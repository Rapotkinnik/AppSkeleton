#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <functional>

#include <QEvent>
#include <QLabel>
#include <QMenuBar>
#include <QMouseEvent>
#include <QMainWindow>

#include <QPropertyAnimation>

#include "MessageWidget.h"

#define mainWindow (QCoreApplication::instance()->findChild<MainWindow *>());

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  using Reaction = std::function<void (QAction *)>;

  explicit MainWindow(QWidget* parent = 0);
  virtual ~MainWindow() = default;

  void addMenu(QMenu* menu);
  QMenu* addMenu(const QString& name);
  QAction *addAction(const QString &name);
  QAction *addAction(const QString &name, Reaction reaction);
  //  TODO: Сделать добавление и получение меню через составное имя : menu/sub_menu/action

  void setIcon(const QIcon& icon);
  void setAnimationType(QEasingCurve::Type type = QEasingCurve::Linear);

  bool loadStyleSheet(const QString& cssFileName);

  void showMessage(const QString& test, MessageWidget::MessageTypes type, unsigned int hideAfter = 0);
  void showMessage(QWidget *widget, MessageWidget::MessageTypes type, unsigned int hideAfter = 0);

  void animatedShowMessage(const QString& test, MessageWidget::MessageTypes type, unsigned int hideAfter = 0);
  void animatedShowMessage(QWidget *widget, MessageWidget::MessageTypes type, unsigned int hideAfter = 0);

 signals:
  void signalActionTriggered(QAction* action);

 protected:
  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual bool eventFilter(QObject* object, QEvent* event);

 private:
  QPoint _positionShift;

  QToolBar* _toolBar;
  QAction* _spacerAction;
  QLabel* _iconLable;
};

#endif  // MAINWINDOW_H

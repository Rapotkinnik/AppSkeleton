#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QLayout>
#include <QLabel>
#include <QFile>
#include <QDir>

#include <QPropertyAnimation>

#include "MessageWidget.h"

#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPoint _positionShift;

    QToolBar *_toolBar;
    QAction *_spacerAction;
    QLabel *_iconLable;

    virtual bool eventFilter(QObject *object, QEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

public:

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void addMenu(QMenu *menu);
    QMenu *addMenu(QString name);
    void setIcon(const QIcon &icon);

    bool loadStyleSheet(const QString &cssFileName);

    void showMessage(const QString &test, MessageWidget::MessageTypes, unsigned int hideAfter = 0);
    void animatedShowMessage(const QString &test, MessageWidget::MessageTypes,
                             unsigned int hideAfter = 0, QEasingCurve::Type = QEasingCurve::Linear);

signals:
    void signalActionTriggered(QAction *action);

public slots:
};

#endif // MAINWINDOW_H

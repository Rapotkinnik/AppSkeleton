#include "MainWindow.h"

#include <QFile>
#include <QLayout>
#include <QTextStream>
#include <QToolBar>
#include <QToolButton>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      _positionShift(QPoint(0, 0)),
      _toolBar(new QToolBar(this)),
      _iconLable(new QLabel(this))
{
  setObjectName("MainWindow");
  setWindowFlags(Qt::FramelessWindowHint);
  setContextMenuPolicy(Qt::NoContextMenu);
  setMouseTracking(true);

  QMainWindow::addToolBar(Qt::TopToolBarArea, _toolBar);
  _toolBar->setObjectName("MenuToolBar");
  _toolBar->setMovable(false);
  _toolBar->setContextMenuPolicy(Qt::NoContextMenu);

  QWidget* spacerWidget = new QWidget(_toolBar);
  spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  _toolBar->addWidget(_iconLable);
  _spacerAction = _toolBar->addWidget(spacerWidget);

  _toolBar->installEventFilter(this);
  spacerWidget->installEventFilter(this);

  // TODO: Зафигачить механизм загрузки всего стиля от css до иконок основных кнопочек (крестик закрытия)
  QAction* closeAction = _toolBar->addAction(QIcon(":/icons/cross_grey"), QString::null);

  loadStyleSheet(":/css/dark_theme");

  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::addMenu(QMenu* menu)
{
  QToolButton* toolButton = new QToolButton(_toolBar);
  toolButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
  toolButton->setText(menu->title());
  toolButton->setMenu(menu);
  toolButton->setPopupMode(QToolButton::InstantPopup);
  toolButton->setStyleSheet("QToolButton::menu-indicator { width: 0px; }");

  _toolBar->insertWidget(_spacerAction, toolButton);

  connect(toolButton, SIGNAL(triggered(QAction*)), this, SIGNAL(signalActionTriggered(QAction*)));
}

QMenu* MainWindow::addMenu(const QString& name)
{
  auto submenus = name.split('/');
  auto topMenuName = submenus.first();

  QList<QAction*> actions = _toolBar->actions();
  foreach (QAction* action, actions)
    if (action->text() == name)
    {
      QToolButton* toolButton = dynamic_cast<QToolButton*>(_toolBar->widgetForAction(action));
      if (toolButton != nullptr)
        return toolButton->menu();
    }

  QMenu* menu = new QMenu(name);
  addMenu(menu);

  return menu;
}

QAction* MainWindow::addAction(const QString &name)
{
  auto menu = addMenu(name.left(name.lastIndexOf('/') - 1));
  auto action = menu->addAction(name.split('/').last());

  connect(action, &QAction::triggered, [this, action](auto /*triggered*/) {
    emit this->signalActionTriggered(action);
  });

  return action;
}

QAction* MainWindow::addAction(const QString &name, Reaction reaction)
{
  auto action = addAction(name);

  connect(action, &QAction::triggered, [action, reaction](auto /*triggered*/) {\
    reaction(action);
  });

  return action;
}

void MainWindow::setIcon(const QIcon& icon)
{
  _iconLable->setPixmap(icon.pixmap(QSize(_toolBar->height(), _toolBar->height())));
}

bool MainWindow::loadStyleSheet(const QString& cssFileName)
{
  if (cssFileName.isEmpty())
    return false;

  QFile cssFile(cssFileName);
  //    cssFile.setFileName(cssFileName);

  if (!cssFile.open(QIODevice::ReadOnly))
    return false;

  QTextStream stream(&cssFile);
  QString cssString = stream.readAll();

  cssFile.close();

  if (cssString.isEmpty())
    return false;

  QMainWindow::setStyleSheet(cssString);  //Применить только к наследникам MainWindow(this)
  //    qApp->setStyleSheet(cssString);//Применить ко всему приложению, но требуется объект QApplication

  return true;
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
  if (event->type() == QEvent::MouseButtonPress)
  {
    QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
    if (mouseEvent != nullptr)
      _positionShift = QMainWindow::pos() - mouseEvent->globalPos();

    return false;
  }

  if (event->type() == QEvent::MouseMove /*&& object->objectName() == QString("MainMenu")*/)
  {
    QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
    if (mouseEvent != nullptr)
      QMainWindow::move(mouseEvent->globalPos() + _positionShift);

    return false;
  }

  return QObject::eventFilter(object, event);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
  //    if (event->buttons() == Qt::NoButton)
  //    {
  //        if (event->pos() == QMainWindow::rect().topLeft() ||
  //            event->pos() == QMainWindow::rect().bottomRight())
  //            QMainWindow::setCursor(Qt::SizeFDiagCursor);
  //        else
  //            if (event->pos() == QMainWindow::rect().bottomLeft() ||
  //                event->pos() == QMainWindow::rect().topRight())
  //                QMainWindow::setCursor(Qt::SizeBDiagCursor);
  //            else
  //               QMainWindow::setCursor(Qt::ArrowCursor);
  //    }

  //    if (event->buttons() == Qt::LeftButton)
  //        MainWindow::resize(QMainWindow::size() + )

  QMainWindow::mouseMoveEvent(event);
}

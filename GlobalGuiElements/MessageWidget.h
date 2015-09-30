#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>

class MessageWidget : public QWidget
{
    Q_OBJECT

public:
    enum MessageTypes
    {
        Ok = 0,
        Info,
        Error,
        Warrning
    };

    explicit MessageWidget(QWidget *parent = 0);
    ~MessageWidget();

signals:

public slots:
};

#endif // MESSAGEWIDGET_H

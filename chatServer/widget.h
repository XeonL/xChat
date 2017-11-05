#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
#include "xtcpserver.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_listenButton_clicked();
    void updateListenStatus(const QString &);


private:
    Ui::Widget *ui;
    xTcpServer *myTcpServer;

};

#endif // WIDGET_H

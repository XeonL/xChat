#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "xclienttcpsocket.h"
#include "xclientudpsocket.h"
#include "loginwindow.h"

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
    void on_connectButton_clicked();
    void beginLogin();


private:
    Ui::Widget *ui;
    xClientTcpSocket *myTcpSocket;
    xClientUdpSocket *myUdpSocket;
    LoginWindow *loginWindow;
};

#endif // WIDGET_H

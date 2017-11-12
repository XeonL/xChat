#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "xclienttcpsocket.h"
#include "xclientudpsocket.h"
#include "loginwindow.h"
#include "userwindow.h"

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
    void readMessage();
signals:
    void updateUserList(QString const &);
    void UserLogin(QString const &);
private:
    void registerResult(QString &);
    void foundResult(QString &);
    void loginResult(QString &);
    Ui::Widget *ui;
    xClientTcpSocket *myTcpSocket;
    xClientUdpSocket *myUdpSocket;
    LoginWindow *loginWindow;
    UserWindow *userWindow;

};

#endif // WIDGET_H

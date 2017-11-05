#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "xclienttcpsocket.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(xClientTcpSocket *socket,QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_signUpButton_clicked();

    void on_foundPasswordButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::LoginWindow *ui;
    xClientTcpSocket *myTcpSocket;
};

#endif // LOGINWINDOW_H

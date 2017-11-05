#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>
#include "xclienttcpsocket.h"

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWindow(xClientTcpSocket *, QWidget *parent = 0);
    ~SignupWindow();

private slots:
    void on_back_clicked();

    void on_signup_clicked();

signals:
    void returnBack();
private:
    Ui::SignupWindow *ui;
    xClientTcpSocket *myTcpSocket;
    void clear();
};

#endif // SIGNUPWINDOW_H

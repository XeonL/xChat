#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QLineEdit>
#include <QCheckBox>
LoginWindow::LoginWindow(xClientTcpSocket *socket,QWidget *parent) :
    QWidget(parent),myTcpSocket(socket),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    //设置密码框非明文显示
    ui->password->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_signUpButton_clicked()
{

}

void LoginWindow::on_foundPasswordButton_clicked()
{

}

void LoginWindow::on_loginButton_clicked()
{

}



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
    signupWindow = new SignupWindow();
    connect(signupWindow,SIGNAL(returnBack()),this,SLOT(show()));
    connect(signupWindow,SIGNAL(signup(QString&,QString&,QString&,QString&)),this,SLOT(signUpToServer(QString&,QString&,QString&,QString&)));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_signUpButton_clicked()
{

    signupWindow->show();
    this->hide();
}

void LoginWindow::on_foundPasswordButton_clicked()
{

}

void LoginWindow::on_loginButton_clicked()
{

}

void signUpToServer(QString &,QString &,QString &,QString &) {

}


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
    signupWindow = new SignupWindow(myTcpSocket);
    foundAccountWindow = new FoundAccountWindow(myTcpSocket);
    connect(signupWindow,SIGNAL(returnBack()),this,SLOT(show()));
    connect(foundAccountWindow,SIGNAL(returnBack()),this,SLOT(show()));
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
    foundAccountWindow->show();
    this->hide();
}

void LoginWindow::on_loginButton_clicked()
{
    QString str = QString("login#");
    str += ui->username->text();
    str += "#";
    str += ui->password->text();
    QByteArray block = str.toLatin1();
    myTcpSocket->write(block);
    qDebug() << QString(block);
}



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
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << tr("login");
    out << ui->username->text();
    out << ui->password->text();
    myTcpSocket->write(block);
    qDebug() << QString(block);
}



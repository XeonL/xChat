#include "widget.h"
#include "ui_widget.h"
#include "message.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myTcpSocket = new xClientTcpSocket(this);
    loginWindow = new LoginWindow(myTcpSocket);
    userWindow = new UserWindow(myTcpSocket);
    connect(myTcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(myTcpSocket,SIGNAL(connected()),this,SLOT(beginLogin()));
    connect(this,&Widget::updateUserList,userWindow,&UserWindow::updateUserList);
    connect(this,&Widget::UserLogin,userWindow,&UserWindow::updateInfo);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_connectButton_clicked()
{
    myTcpSocket->abort();
    myTcpSocket->connectToHost(ui->addressText->text(),
                               ui->portText->text().toInt());
}
void Widget::beginLogin() {

    loginWindow->show();
    this->hide();
}
void Widget::readMessage() {

    QString data = QString(myTcpSocket->readAll());
    qDebug() << data;
    QString type = data.split("#")[0];
    if(type == "login") {
        loginResult(data);
    } else if(type == "register") {
        registerResult(data);
    } else if(type == "found") {
        foundResult(data);
    } else if(type == "userlist") {
        this->hide();
        loginWindow->hide();
        userWindow->show();
        emit updateUserList(data);
    }
}

void Widget::registerResult(QString &data) {
    QStringList list = data.split("#");
    if(list[1]=="true") {
        QMessageBox::warning(nullptr,QString("注册信息"),QString("注册成功！"),QMessageBox::Yes);
    } else if(list[2]=="1") {
        QMessageBox::warning(nullptr,QString("注册信息"),QString("注册失败，请重试！"),QMessageBox::Yes);
    } else if(list[2]=="2") {
        QMessageBox::warning(nullptr,QString("注册信息"),QString("用户名已存在，请重试！"),QMessageBox::Yes);
    }

}

void Widget::foundResult(QString &data) {
    QStringList list = data.split("#");
    if(list[1]=="true") {
        QMessageBox::warning(nullptr,QString("找回密码"),QString("密码：%1").arg(list[2]),QMessageBox::Yes);
    } else {
        QMessageBox::warning(nullptr,QString("找回密码"),QString("该用户不存在或学号错误！"),QMessageBox::Yes);
    }
}

void Widget::loginResult(QString &data) {
    QStringList list = data.split("#");
    if(list[1]=="true") {
        loginWindow->hide();
        userWindow->show();
        emit UserLogin(list[2]);

    } else {
        QMessageBox::warning(nullptr,QString("登录信息"),QString("用户名或密码错误，请重新输入！"),QMessageBox::Yes);
    }
}

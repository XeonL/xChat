#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QHostAddress>

ChatWindow::ChatWindow(qintptr hand,QWidget *parent) :
    QWidget(parent),type(false),handle(hand),
    ui(new Ui::ChatWindow),sign(false)
{
    ui->setupUi(this);
}
ChatWindow::ChatWindow(QString &username1,QString &ip1,QWidget *parent) :
    QWidget(parent),type(true),username(username1),
    ip(ip1),
    ui(new Ui::ChatWindow),sign(false)
{
    ui->setupUi(this);
}
ChatWindow::~ChatWindow()
{
    delete ui;
}
void ChatWindow::initialize() {
    tcpsocket = new QTcpSocket(this);
    connect(tcpsocket,&QTcpSocket::disconnected,this,&ChatWindow::sockDisConnect);
    connect(tcpsocket,&QTcpSocket::readyRead,this,&ChatWindow::readMessage);
    if(type) {
        tcpsocket->setSocketDescriptor(handle);
        QString newIp = (tcpsocket->peerAddress()).toString().mid(7);
        ip = newIp;
    } else {
//        tcpsocket->connectToHost(ip,8888);
        sign = true;
    }
}
void ChatWindow::sendChatMessage(const QString &data) {
    QByteArray block = data.toUtf8();
    if(sign) {
        if(tcpsocket==nullptr) {
            tcpsocket = new QTcpSocket();
            connect(tcpsocket,&QTcpSocket::disconnected,this,&ChatWindow::sockDisConnect);
            connect(tcpsocket,&QTcpSocket::readyRead,this,&ChatWindow::readMessage);
        }
        tcpsocket->connectToHost(ip,8888);
        sign = false;
    }
    tcpsocket->write(block);
}
void ChatWindow::sockDisConnect() {
    delete tcpsocket;
    tcpsocket = nullptr;
//    emit sockDisconnectedSignal();
    sign = true;
}

void ChatWindow::on_sendMessageButton_clicked()
{
    QString str = ui->messageLine->text();
    ui->messageList->addItem(str);
    sendChatMessage(str);
}
void ChatWindow::readMessage() {
    QString str = QString(tcpsocket->readAll());
    ui->messageList->addItem(str);
}

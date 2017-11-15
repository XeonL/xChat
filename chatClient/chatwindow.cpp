#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QDebug>
ChatWindow::ChatWindow(QString &username,QString anothername,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    userName = username;
    anotherUserName = anothername;
    ui->userName->setText(anotherUserName);
}

ChatWindow::~ChatWindow()
{
    delete ui;
    delete fileReceiver;
}

void ChatWindow::on_sendButton_clicked()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    QString message = userName + " " + current_date + " : " + ui->messageInput->text();
    qDebug() << "wait to send : " << message;
    ui->messageList->addItem(message);
    emit newMessageToSend(message);
}
void ChatWindow::newMessageGet(const QString &message) {
    qDebug() << "get message:" << message;
    ui->messageList->addItem(message);
    if(anotherUserName=="") {
        QStringList list = message.split(" ");
        anotherUserName = list[0];
        ui->userName->setText(anotherUserName);
    }
}



void ChatWindow::on_sendFile_clicked()
{
    FileWindow *newFileWindow = new FileWindow(anotherIp);
    newFileWindow->show();
    newFileWindow->setAttribute(Qt::WA_DeleteOnClose);
}
void ChatWindow::setAnotherIp(const QString &ip) {
    anotherIp = ip;

    fileReceiver = new UrtReceiver(anotherIp);
}

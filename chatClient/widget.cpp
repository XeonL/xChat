#include "widget.h"
#include "ui_widget.h"
#include "message.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),blockSize(0),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myTcpSocket = new xClientTcpSocket(this);
    loginWindow = new LoginWindow(myTcpSocket);
    connect(myTcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(myTcpSocket,SIGNAL(connected()),this,SLOT(beginLogin()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_connectButton_clicked()
{
    blockSize = 0;
    myTcpSocket->abort();
    myTcpSocket->connectToHost(ui->addressText->text(),
                               ui->portText->text().toInt());
}
void Widget::beginLogin() {

    loginWindow->show();
    this->hide();
}
void Widget::readMessage() {
    qDebug() << "readready";
    QDataStream in(myTcpSocket);
    QString message;
    in.setVersion(QDataStream::Qt_5_9);
    if(blockSize==0) {
        if(myTcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> blockSize;
    }
    if(myTcpSocket->bytesAvailable() < blockSize) return;
    in >> message;
    Message * m = new Message();
    m->setText(message);
    m->show();
}

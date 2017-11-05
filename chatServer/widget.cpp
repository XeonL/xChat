#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_listenButton_clicked()
{
    ui->listenButton->setText(QString(u8"正在监听"));
    ui->listenButton->setEnabled(false);
    myTcpServer = new xTcpServer(this);
    connect(myTcpServer,SIGNAL(listenStatusChange(const QString &)),this,SLOT(updateListenStatus(const QString &)));
    myTcpServer->startServer();

}

void Widget::updateListenStatus(const QString &status) {
    ui->listenStatus->setText(status);

}

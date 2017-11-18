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
    connect(myTcpServer,&xTcpServer::broadcastListSignal,this,&Widget::updateList);
    myTcpServer->startServer();

}

void Widget::updateListenStatus(const QString &status) {
    ui->listenStatus->setText(status);

}

void Widget::updateList(const QString &str) {
    QStringList list = str.split("#");
    if(list[0]=="userlist") {
        ui->onlineList->clear();
        int max = list.count();
        int i = 1;
        while(i < max) {
            ui->onlineList->addItem(list[i]);
            i+=2;;
        }
    } else if(list[0]=="offlinelist") {
        ui->offlineList->clear();
        int max = list.count();
        int i = 1;
        while(i < max) {
            ui->offlineList->addItem(list[i]);
            i++;
        }
    }

}

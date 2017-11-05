#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myTcpSocket = new xClientTcpSocket(this);
    connect(myTcpSocket,SIGNAL(connected()),this,SLOT(beginLogin()));

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
    loginWindow = new LoginWindow(myTcpSocket);

    loginWindow->show();
    this->hide();
}

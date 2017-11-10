#include "foundaccountwindow.h"
#include "ui_foundaccountwindow.h"

FoundAccountWindow::FoundAccountWindow(xClientTcpSocket *socket,QWidget *parent) :
    QWidget(parent),myTcpSocket(socket),
    ui(new Ui::FoundAccountWindow)
{
    ui->setupUi(this);
}

FoundAccountWindow::~FoundAccountWindow()
{
    delete ui;
}

void FoundAccountWindow::on_back_clicked()
{
    clear();
    emit returnBack();
    this->hide();

}

void FoundAccountWindow::on_foundButton_clicked()
{
    QString str = QString("found#");
    str += ui->username->text();
    str += "#";
    str += ui->stuNum->text();
    QByteArray block = str.toLatin1();
    myTcpSocket->write(block);
    qDebug() << QString(block);
}
void FoundAccountWindow::clear() {
    ui->username->clear();
    ui->stuNum->clear();
}

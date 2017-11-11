#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(xClientTcpSocket *socket,QWidget *parent) :
    QWidget(parent),tcpSocket(socket),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
}

UserWindow::~UserWindow()
{
    delete ui;
}
void UserWindow::updateUserList(const QString &data) {

}

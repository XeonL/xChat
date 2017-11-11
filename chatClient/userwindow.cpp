#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(xClientTcpSocket *socket,QWidget *parent) :
    QWidget(parent),tcpSocket(socket),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    userList = new QHash<QString,QString>();
}

UserWindow::~UserWindow()
{
    delete ui;
}
void UserWindow::updateUserList(const QString &data) {
    QStringList list = data.split("#");
    int len = list.count()/2;
    userList->clear();
    ui->userList->clear();
    for(int i=1;i<=len;i++) {
        userList->insert(list[i],list[i+1].mid(7));
        ui->userList->addItem(list[i]);
    }
}

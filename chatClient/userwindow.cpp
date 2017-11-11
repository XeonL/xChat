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
    for(int i=1;i<=len;i+=2) {
        userList->insert(list[i],list[i+1].mid(7));
        ui->userList->addItem(list[i]);
    }
}

void UserWindow::on_chatbutton_clicked()
{
    QString user = ui->usernameToChat->text();
    QString ip = userList->value(user);
    if(ip=="") {
        QMessageBox::warning(nullptr,"Warning","请输入在线用户的用户名！",QMessageBox::Yes);
    }
}

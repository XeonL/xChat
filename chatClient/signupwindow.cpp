#include "signupwindow.h"
#include "ui_signupwindow.h"

SignupWindow::SignupWindow(xClientTcpSocket *socket,QWidget *parent) :
    QWidget(parent),myTcpSocket(socket),
    ui(new Ui::SignupWindow)
{
    ui->setupUi(this);
}

SignupWindow::~SignupWindow()
{
    delete ui;
}

void SignupWindow::on_back_clicked()
{
    clear();
    this->hide();
    emit returnBack();
}

void SignupWindow::on_signup_clicked()
{


}

void SignupWindow::clear() {
    ui->nickName->clear();
    ui->password->clear();
    ui->username->clear();
    ui->stuNum->clear();
}

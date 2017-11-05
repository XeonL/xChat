#include "signupwindow.h"
#include "ui_signupwindow.h"

SignupWindow::SignupWindow(QWidget *parent) :
    QWidget(parent),
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

    emit signup(ui->username->text(),ui->nickName->text(),
                ui->password->text(),ui->stuNum->text());

}

void clear() {
    ui->nickName->setText("");
    ui->password->setText("");
    ui->username->setText("");
    ui->stuNum->setText("");
}

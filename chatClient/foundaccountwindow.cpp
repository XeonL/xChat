#include "foundaccountwindow.h"
#include "ui_foundaccountwindow.h"

FoundAccountWindow::FoundAccountWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FoundAccountWindow)
{
    ui->setupUi(this);
}

FoundAccountWindow::~FoundAccountWindow()
{
    delete ui;
}

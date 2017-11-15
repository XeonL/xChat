#include "filewindow.h"
#include "ui_filewindow.h"

FileWindow::FileWindow(QString const &address,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    ip = address;
}

FileWindow::~FileWindow()
{
    delete ui;
    delete fileSender;
    delete timer;
}

void FileWindow::on_open_clicked()
{
    filename = QFileDialog::getOpenFileName(this,tr("open"));
        if(filename.isEmpty()) {
            return;
        }

        QFile file(filename);
    //    file.open(QFile::ReadOnly);
        QStringList list = filename.split("/");

        QString name = list[list.count()-1];
        ui->status->setText(QString("%1 size:%2bytes").arg(name).arg(file.size()));
}

void FileWindow::on_beginSend_clicked()
{
//    if(fileSender) {
//        delete fileSender;
//    }
    qDebug() << "filename " << filename;
    qDebug() << "begin send file" << ip;
    fileSender = new UrtSender(ip,24356,filename);
    fileSender->start();
    connect(fileSender,&UrtSender::fileSuccess,this,&FileWindow::fileSuccess);
    connect(fileSender,&UrtSender::progress,this,&FileWindow::updateProgress);
    timer = new QTimer();
    timer->setInterval(500);
    connect(timer,&QTimer::timeout,this,&FileWindow::updateV);
    timer->start();
}
void FileWindow::updateProgress(quint64 total, quint64 now) {
    ui->sendProgress->setMaximum(total);
    ui->sendProgress->setValue(now);
    send = now;
}
void FileWindow::fileSuccess() {
    timer->stop();
    QMessageBox::warning(nullptr,"success","发送成功！");
}
void FileWindow::updateV() {
    time += 0.5;
    double v = send/time;
    QString str = "";
    str+=v;
    ui->status->setText(str);
}

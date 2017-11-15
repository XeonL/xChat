#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include "urtsender.h"
#include <QTimer>
#include <QMessageBox>

namespace Ui {
class FileWindow;
}

class FileWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FileWindow(QString const &address,QWidget *parent = 0);
    ~FileWindow();

private slots:
    void on_open_clicked();

    void on_beginSend_clicked();
    void updateProgress(quint64,quint64);
    void fileSuccess();
    void updateV();

private:

    Ui::FileWindow *ui;
    UrtSender *fileSender;
    QString filename;
    QString ip;
    double time;
    quint64 send;
    QTimer *timer;
};

#endif // FILEWINDOW_H

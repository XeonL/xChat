#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QDateTime>
#include "urtreceiver.h"
#include "filewindow.h"
namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QString &username,QString anothername = "",QWidget *parent = 0);
    ~ChatWindow();
signals:
    void newMessageToSend(QString const &);
private slots:
    void on_sendButton_clicked();
    void on_sendFile_clicked();
public slots:
    void setAnotherIp(QString const &);

public slots:
    void newMessageGet(QString const &);
private:
    Ui::ChatWindow *ui;
    QString userName;
    QString anotherUserName;
    QString anotherIp;
    UrtReceiver *fileReceiver;
};

#endif // CHATWINDOW_H

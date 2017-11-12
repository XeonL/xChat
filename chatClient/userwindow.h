#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include "xclienttcpsocket.h"
#include <QHash>
#include <QMessageBox>
#include "tcpserver.h"
#include "worker.h"
#include "chatwindow.h"
#include <QVector>
namespace Ui {
class UserWindow;
}

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserWindow(xClientTcpSocket *,QWidget *parent = 0);
    ~UserWindow();
public slots:
    void updateUserList(QString const &);
    void updateInfo(QString const &);
    void updateOfflineList(QString const &);
    void getOfflineMessage(QString const &);

private slots:
    void on_chatbutton_clicked();

    void on_offlineMessageButton_clicked();

private:
    void newChatWindow1(qintptr descriptor);
    void newChatWindow(QString const &,QString const &);
    Ui::UserWindow *ui;
    xClientTcpSocket *tcpSocket;
    QHash<QString,QString> *userList;
    QVector<QString> *offlineList;
    tcpServer *server;
    QString myName;
};

#endif // USERWINDOW_H

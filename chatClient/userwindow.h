#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include "xclienttcpsocket.h"
#include <QHash>
#include <QMessageBox>
#include "tcpserver.h"
#include "chatwindow.h"
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
private slots:
    void on_chatbutton_clicked();

private:
    Ui::UserWindow *ui;
    xClientTcpSocket *tcpSocket;
    QHash<QString,QString> *userList;
    tcpServer *server;
};

#endif // USERWINDOW_H

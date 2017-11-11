#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include "xclienttcpsocket.h"

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
private:
    Ui::UserWindow *ui;
    xClientTcpSocket *tcpSocket;
};

#endif // USERWINDOW_H

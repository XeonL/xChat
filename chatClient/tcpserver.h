#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include "chatwindow.h"
class tcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit tcpServer(QObject *parent = 0);
    ~tcpServer();
protected:
    void incomingConnection(qintptr handle);
private:
};

#endif // TCPSERVER_H

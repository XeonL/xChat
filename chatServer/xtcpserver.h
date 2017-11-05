#ifndef XTCPSERVER_H
#define XTCPSERVER_H
#define PORT 6666

#include <QTcpServer>
#include <QObject>
#include "xservertcpsocket.h"

class xTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit xTcpServer(QObject *parent = 0);
    void startServer();
signals:
    void listenStatusChange(const QString &status);
protected:
    void incomingConnection(qintptr socketDescriptor);

};

#endif // XTCPSERVER_H

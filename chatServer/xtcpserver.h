#ifndef XTCPSERVER_H
#define XTCPSERVER_H
#define PORT 6666

#include <QTcpServer>
#include "xservertcpsocket.h"

class xTcpServer : public QtcpServer
{
public:
    explicit xTcpServer(QObject *parent = 0);
    void startServer();
protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // XTCPSERVER_H

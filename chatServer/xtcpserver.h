#ifndef XTCPSERVER_H
#define XTCPSERVER_H
#define PORT 6666

#include <QTcpServer>
#include <QVector>
#include "xservertcpsocket.h"
#include "xserverthread.h"

class xTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit xTcpServer(QObject *parent = 0);
    ~xTcpServer();
    void startServer();
signals:
    void listenStatusChange(const QString &status);
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    QVector<xServerThread *> threadPool;

};

#endif // XTCPSERVER_H

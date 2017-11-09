#ifndef XTCPSERVER_H
#define XTCPSERVER_H
#define PORT 6666

#include <QTcpServer>
#include "xservertcpsocket.h"
#include <QHash>


class xTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit xTcpServer(QObject *parent = 0);
    ~xTcpServer();
    void startServer();
signals:
    void listenStatusChange(const QString &status);
public slots:
    void addSocket(xServerTcpSocket *,int);
    void removeSocket(int);
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    QHash<int,xServerTcpSocket *> * clientPool;

};

#endif // XTCPSERVER_H

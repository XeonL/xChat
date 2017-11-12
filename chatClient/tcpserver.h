#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class tcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit tcpServer(QObject *parent = 0);
    ~tcpServer();
signals:
    void newConnection(qintptr descriptor);
protected:
    void incomingConnection(qintptr handle);
private:
};

#endif // TCPSERVER_H

#ifndef WORKER_H
#define WORKER_H
#include "xservertcpsocket.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(qintptr descriptor,QObject *parent = nullptr);

signals:
    void newTcpSocket(xServerTcpSocket *,int);
    void socketWaitRemove(int);
    void socketDisconnect();
public slots:
    void initialize();
    void readData();

private:
    void sendSignalOfDisconnect();
    xServerTcpSocket *tcpSocket;
    qintptr socketDescriptor;
};
#endif // WORKER_H

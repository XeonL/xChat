#ifndef WORKER_H
#define WORKER_H
#include "xservertcpsocket.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(qintptr descriptor,QObject *parent = nullptr);
    void sendMessageToClient(QString const &);

signals:
    void newTcpSocket(xServerTcpSocket *,int);
    void socketWaitRemove(int);
    void socketDisconnect();
    //来自客户端的message
//    void readMessage(QString const &);
    void newRegister();
    void newLogin(int handle,QString const &username);

public slots:
    void initialize();
    void readData();

private:
    void sendSignalOfDisconnect();

    xServerTcpSocket *tcpSocket;
    qintptr socketDescriptor;
};
#endif // WORKER_H

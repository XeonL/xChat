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
    void addOfflineMessage(QString const &,QString const &);

public slots:
    void initialize();
    void readData();
    void broadcastUserList(QString const &);
    void sendOfflineMessage(QString const &,QString const &);

private:
    void sendSignalOfDisconnect();
    bool isLogined;
    xServerTcpSocket *tcpSocket;
    qintptr socketDescriptor;
    QString username;
};
#endif // WORKER_H

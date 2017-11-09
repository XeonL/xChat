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
    void accountInfo(quint8 type,QString &username,QString &password = QString(),
                     QString &nickname = QString(),QString &stunum = QString());
public slots:
    void initialize();
    void readData();

private:
    void sendSignalOfDisconnect();
    xServerTcpSocket *tcpSocket;
    qintptr socketDescriptor;
    quint16 blockSize;
    quint8 dataType;
};
#endif // WORKER_H

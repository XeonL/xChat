#ifndef XSERVERTHREAD_H
#define XSERVERTHREAD_H
#include <QThread>
#include "xservertcpsocket.h"
class xServerThread : public QThread
{
    Q_OBJECT
public:
    xServerThread(qintptr descriptor,QObject *parent = 0);
    void run();

private:
    xServerTcpSocket *myTcpSocket;
    qintptr socketDescriptor;
};

#endif // XSERVERTHREAD_H

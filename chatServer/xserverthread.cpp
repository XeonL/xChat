#include "xserverthread.h"

xServerThread::xServerThread(qintptr descriptor,QObject *parent) :
    socketDescriptor(descriptor),QThread(parent)
{
    myTcpSocket = new xServerTcpSocket(this);
    if(!myTcpSocket->setSocketDescriptor(socketDescriptor)) {
        qDebug() << "Can not set socketDescriptor!";
    }
}
void xServerThread::run() {

}

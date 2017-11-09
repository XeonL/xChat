#include "xserverthread.h"
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QHostAddress>
xServerThread::xServerThread(qintptr descriptor,QObject *parent) :
    socketDescriptor(descriptor),QThread(parent),end(false)
{
    myTcpSocket = new xServerTcpSocket(this);
    qDebug() << socketDescriptor ;
    if(!myTcpSocket->setSocketDescriptor(socketDescriptor)) {
        qDebug() << "Can not set socketDescriptor!";
    }
    qDebug() << "Connect " ;
    qDebug() << myTcpSocket->peerAddress().toString() << myTcpSocket->peerPort();
    //连接结束自动关闭线程
    connect(myTcpSocket,SIGNAL(disconnected()),this,SLOT(closeThread()));

}
void xServerThread::run() {




    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    qDebug()<<"new thread";
    out<<(quint16)0;
    out<<tr("new thread");
    out.device()->seek(0);
    out<<(quint16)(block.size()-sizeof(quint16));
    myTcpSocket->write(block);
    exec();


}
void xServerThread::closeThread() {
    qDebug() << "disconnect";
    end = true;
}

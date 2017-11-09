#include "xtcpserver.h"
#include <QObject>
#include <QDebug>
#include <QThread>
#include "worker.h"
#include "xservertcpsocket.h"
xTcpServer::xTcpServer(QObject *parent) :
    QTcpServer(parent)
{
    clientPool = new QHash<int,xServerTcpSocket *>;
}
xTcpServer::~xTcpServer() {

}

void xTcpServer::startServer() {
    if(!this->listen(QHostAddress::Any,PORT)) {
        qDebug() << "Could not start server";
        emit listenStatusChange(QString("Could not start server"));

    } else {
        qDebug() << "Listening to port " << this->serverPort() << "...";
        emit listenStatusChange(QString("Listening to port %1 ...").arg(this->serverPort()));
    }
}

void xTcpServer::incomingConnection(qintptr socketDescriptor) {
    qDebug() << socketDescriptor << " Connecting...";
//    xServerThread *thread = new xServerThread(socketDescriptor,this);
//    //添加入线程池以便程序关闭时结束进程
//    threadPool.append(thread);
//    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
//    thread->start();

    Worker * newWorker = new Worker(socketDescriptor);
    QThread *thread = new QThread();
    connect(thread,&QThread::started,newWorker,&Worker::initialize);
    connect(newWorker,&Worker::newTcpSocket,this,&xTcpServer::addSocket);
    connect(newWorker,&Worker::socketDisconnect,thread,&QThread::quit);
    connect(newWorker,&Worker::socketDisconnect,newWorker,&Worker::deleteLater);
    connect(newWorker,&Worker::socketWaitRemove,this,&xTcpServer::removeSocket);

    newWorker->moveToThread(thread);
    thread->start();
}

void xTcpServer::addSocket(xServerTcpSocket *socket, int descriptor) {
    clientPool->insert(descriptor,socket);
}

void xTcpServer::removeSocket(int descriptor) {
    xServerTcpSocket *tcp = clientPool->value(descriptor);
    clientPool->remove(descriptor);
    delete tcp;
    qDebug()<<"remove socket from pool";
}

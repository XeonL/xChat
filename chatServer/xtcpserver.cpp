#include "xtcpserver.h"
#include <QObject>
#include <QDebug>
#include "xserverthread.h"
#include "xservertcpsocket.h"
xTcpServer::xTcpServer(QObject *parent) :
    QTcpServer(parent),threadPool()
{

}
xTcpServer::~xTcpServer() {
//    ~QTcpServer();
    auto begin = threadPool.begin();
    auto end = threadPool.end();
    while(begin!=end) {
        if(begin) {
            (*begin)->terminate();
            delete *begin;
            (*begin) = nullptr;
        }
        begin++;
    }
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
    xServerThread *thread = new xServerThread(socketDescriptor,this);
    //添加入线程池以便程序关闭时结束进程
    threadPool.append(thread);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();

}

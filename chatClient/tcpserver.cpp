#include "tcpserver.h"

tcpServer::tcpServer(QObject *parent) :
    QTcpServer(parent)
{
    this->listen(QHostAddress::Any,8888);
}
tcpServer::~tcpServer() {

}
void tcpServer::incomingConnection(qintptr handle) {

    emit newConnection(handle);
}

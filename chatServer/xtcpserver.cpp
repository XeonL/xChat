#include "xtcpserver.h"
# include <QObject>
# include <QDebug>
xTcpServer::xTcpServer(QObject *parent = 0) :
    QTcpServer(parent)
{

}

void xTcpServer::startServer() {
    int port;
    port = this->listen(QHostAddress::Any,PORT);
    if(!port) {
        qDebug() << "Could not start server";
    } else {
        qDebug() << "Listening to port " << port << "...";
    }
}

void xTcpServer::incomingConnection(qintptr socketDescriptor) {
    qDebug() << socketDescriptor << " Connecting...";
}

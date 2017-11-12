#include "worker.h"
#include "message.h"
Worker::Worker(qintptr handle, QObject *parent) :
    QObject(parent) {
    descriptor = handle;
    active = false;

}
Worker::Worker(QString const &ip, QObject *parent) :
    QObject(parent) {
    anotherIp = ip;
    active = true;

}
Worker::~Worker() {
    delete tcpSocket;
}
void Worker::initialize() {
    qDebug() << "socket initialize";
    tcpSocket = new QTcpSocket();
    if(active) {
        tcpSocket->connectToHost(anotherIp,8888);
        qDebug() << "socket connect to " << anotherIp;
    } else {
        tcpSocket->setSocketDescriptor(descriptor);
        anotherIp = tcpSocket->peerAddress().toString().mid(7);
        qDebug() << "get connect ip " << anotherIp;
    }
    connect(tcpSocket,&QTcpSocket::disconnected,this,&Worker::connectMiss);
    connect(tcpSocket,&QTcpSocket::readyRead,this,&Worker::getMessage);
}
void Worker::connectMiss() {
    isDisconnected = true;
}
void Worker::getMessage() {
    QString data = QString(tcpSocket->readAll());
    qDebug() << "getMessage from " << anotherIp <<":" << data;
    emit newMessage(data);
}
void Worker::sendMessage(QString const &message) {
    if(isDisconnected) {
        delete tcpSocket;
        tcpSocket = new QTcpSocket();
        tcpSocket->connectToHost(anotherIp,8888);
        isDisconnected = false;
    }
    QByteArray block = message.toUtf8();
    tcpSocket->write(block);
}

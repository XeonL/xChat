#include "worker.h"
#include <QDataStream>
//#include <QDebug>
Worker::Worker(qintptr descriptor,QObject *parent) :
    QObject(parent),socketDescriptor(descriptor)
{
    qDebug()<<"new Worker";
}

void Worker::initialize() {
    tcpSocket = new xServerTcpSocket();
    tcpSocket->setSocketDescriptor(socketDescriptor);


//    QByteArray block;
//    QDataStream out(&block,QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_9);
//    qDebug()<<"new thread";
//    out<<(quint16)0;
//    out<<tr("new thread");
//    out.device()->seek(0);
//    out<<(quint16)(block.size()-sizeof(quint16));
//    tcpSocket->write(block);
//    qDebug()<<"sendmessage";

    connect(tcpSocket,&xServerTcpSocket::disconnected,
            this,&Worker::sendSignalOfDisconnect);
    connect(tcpSocket,&xServerTcpSocket::readyRead,this,&Worker::readData);

}

void Worker::readData() {
//    qDebug() << tcpSocket->readAll();
    QString data = QString(tcpSocket->readAll());
    QStringList list = data.split("#");
    qDebug() << "receive message:";
    for(int i=0;i<list.count();i++) {
        qDebug() << list[i];
    }
    qDebug() << data;
}

void Worker::sendSignalOfDisconnect() {
    emit socketWaitRemove(socketDescriptor);
    emit socketDisconnect();
    qDebug()<<"socket:"<<socketDescriptor<<" disconnected";
}

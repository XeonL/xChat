#include "worker.h"
#include <QDataStream>
//#include <QDebug>
Worker::Worker(qintptr descriptor,QObject *parent) :
    QObject(parent),socketDescriptor(descriptor),blockSize(0),
    dataType(0)
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
    //数据格式：quint16的blocksize,quint8的type,其余为对应blocksize大小的结构体
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_9);
    if(blockSize == 0) {
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> blockSize;
    } else if(dataType == 0) {
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint8)) return;
        in >> dataType;
    }
    if(tcpSocket->bytesAvailable() < blockSize) return;
//    in >> data;

    switch(dataType) {
    case 1:{
        //登录


        break;
    }
    case 2:{
        //注册

        break;
    }
    case 3:{
        //找回密码
        break;
    }
    default:{
        //...

    }
    }
    dataType = 0;
    blockSize = 0;
}

void Worker::sendSignalOfDisconnect() {
    emit socketWaitRemove(socketDescriptor);
    emit socketDisconnect();
    qDebug()<<"socket:"<<socketDescriptor<<" disconnected";
}

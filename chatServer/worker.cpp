#include "worker.h"
#include <QDataStream>
#include <QSqlQuery>
#include <QHostAddress>
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
//    QString data = QString(tcpSocket->readAll());
//    QStringList list = data.split("#");
//    qDebug() << "receive message:";
//    for(int i=0;i<list.count();i++) {
//        qDebug() << list[i];
//    }
    QString data = QString(tcpSocket->readAll());
//    emit readMessage(data);
    qDebug() << data;
    qDebug() << "controller";
    QStringList list = data.split("#");
    QSqlQuery query;
    if(list[0] == "login") {
        qDebug() << "login";
        QString str = QString("select * from user where username = '%1' and password = '%2'").
                arg(list[1]).arg(list[2]);
        if(query.exec(str)) {
            if(query.next()) {
                QString message = "login#true";
                sendMessageToClient(message);
                emit newLogin(query.value(1).toString(),
                              query.value(3).toString(),
                              tcpSocket->peerAddress().toString());
                qDebug() << tcpSocket->peerAddress().toString();
            } else {
                QString message = "login#false";
                sendMessageToClient(message);
            }
        } else {
            qDebug() << "login select failed";
        }

    } else if(list[0] == "register") {
        QString str = QString("insert into user values (null,'%1','%2','%3','%4')").
                arg(list[1]).arg(list[2]).arg(list[3]).arg(list[4]);
        qDebug() << "register";
        qDebug() << str;
        if(query.exec(str)) {
            qDebug() << "insert success!";
            emit newRegister();
            QString message = "register#true";
            sendMessageToClient(message);
        } else {
            qDebug() << "insert failed!";
            QString message = "register#false";
            sendMessageToClient(message);
        }
    } else if(list[0] == "found") {
        qDebug() << "found";
        QString str = QString("select * from user where username = '%1' and stunum = '%2'").
                arg(list[1]).arg(list[2]);
        if(query.exec(str)) {
            if(query.next()) {
                qDebug() << "found success";
                QString message = QString("found#true#%1").arg(query.value(2).toString());
                sendMessageToClient(message);
            } else {
                qDebug() << "found noexist";
                QString message = "found#false";
                sendMessageToClient(message);
            }
        } else {
            qDebug() << "found select failed";
        }
    }
}

void Worker::sendSignalOfDisconnect() {
    emit socketWaitRemove(socketDescriptor);
    emit socketDisconnect();
    qDebug()<<"socket:"<<socketDescriptor<<" disconnected";
}

void Worker::sendMessageToClient(const QString &str) {
    QByteArray block = str.toUtf8();
    tcpSocket->write(block);

}

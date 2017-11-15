#include "urtsender.h"
#define SIZE 1024*32
UrtSender::UrtSender(QString const &ip,int portNum,QString &filename,QObject *parent) : QObject(parent)
{
    ipAddress = ip;
    port = portNum;
    fileName = filename;
    QStringList list = fileName.split("/");

    name = list[list.count()-1];
    file = new QFile(fileName);
    file->open(QFile::ReadOnly);
    loadSize = SIZE;
    totalBytes = file->size();
    bytesWritten = 0;
    bytesToWrite = totalBytes;
    pktPool = new QHash<quint64,UdpPkt *>;
    socket = new QUdpSocket();
    listenSocket = new QUdpSocket();
    listenSocket->bind(45454,QUdpSocket::ShareAddress);
    connect(listenSocket,&QUdpSocket::readyRead,this,&UrtSender::processPendingDatagram);
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&UrtSender::tryToBegin);
    endtimer = new QTimer();
    connect(endtimer,&QTimer::timeout,this,&UrtSender::tryToEnd);
    qDebug() << "filename:" << name;
    qDebug() << "sizeof:" << totalBytes;
}
UrtSender::~UrtSender() {
    delete file;
    delete listenSocket;
    delete socket;
    delete timer;
    delete pktPool;
}
void UrtSender::start() {

    timer->setInterval(200);
    timer->start();
    tryToBegin();

}
void UrtSender::processPendingDatagram() {
    while(listenSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(sizeof(quint64));
        listenSocket->readDatagram(datagram.data(),datagram.size());
        QDataStream in(datagram);
        quint64 sign;
        in >> sign;
        messageControl(sign);

    }
}
void UrtSender::tryToBegin() {
//    QString localHostName = QHostInfo::localHostName();
//    qDebug() <<"localHostName: "<<localHostName;
//    QHostInfo info = QHostInfo::fromName(localHostName);
//    qDebug() <<"IP Address: "<<info.addresses();
    QByteArray data;
    data.resize(SIZE+8);
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << (quint64)1;
    out << totalBytes;
    out << (quint64)name.size();
    out << name;
    qDebug() << "name:" << name << " size:" << name.size();
    QHostAddress ip;
    ip.setAddress(ipAddress);
    qDebug() << "try to begin:";
    socket->writeDatagram(data,ip,port);

}
void UrtSender::tryToSend() {
    while(now!=max&&bytesToWrite!=0) {
        now++;
        quint64 size = qMin(loadSize,bytesToWrite);
        QByteArray block = file->read(size);
        bytesToWrite -= size;
        bytesWritten += size;
//        now ++;
        UdpPkt * pkt = new UdpPkt(block,socket,ipAddress,
                                  port,nowNum);
        pktPool->insert(nowNum,pkt);
        qDebug() << "send pkt " << nowNum;
        qDebug() << "bytesWritten:" << bytesWritten;
        qDebug() << "bytesToWrite:" << bytesToWrite;
        emit(totalBytes,bytesWritten);
        //qDebug() << block;
        if(bytesToWrite==0) {
            sendEnd = true;
        } else {
            nowNum++;
        }
    }
}
void UrtSender::tryToEnd() {
    QByteArray data;
    data.resize(SIZE+8);
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << (quint64)0;
    QHostAddress ip;
    ip.setAddress(ipAddress);
    socket->writeDatagram(data,ip,port);
}
void UrtSender::getACK(quint64 num) {
    UdpPkt *p = pktPool->value(num);
    if(p) {
        delete p;
        pktPool->remove(num);
        now--;
        tryToSend();
    }
    qDebug() << "目前还没有收到ack的pkt有" << now << " 个";
}
void UrtSender::messageControl(quint64 sign) {
    qDebug() << "get ACK " << sign;
    if(sign == 1) {
        if(begin) {
            return;
        }
        begin = true;
        timer->stop();
        tryToSend();
    } else if(sign == 0) {
        if(end) {
            return;
        }
        endtimer->stop();
        end = true;
        file->close();
        qDebug() << "文件传输完成！";
        emit fileSuccess();
    } else {
        getACK(sign);
        if(sendEnd&&sign==nowNum) {
            endtimer->setInterval(200);
            endtimer->start();
            tryToEnd();
        }
    }
}

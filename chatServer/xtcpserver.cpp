#include "xtcpserver.h"

#include "worker.h"
#include "xservertcpsocket.h"
xTcpServer::xTcpServer(QObject *parent) :
    QTcpServer(parent)
{
    clientPool = new QHash<int,xServerTcpSocket *>;
    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName("info.db");
    db->open();
    QSqlQuery query;
    bool success = query.exec("CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "username VARCHAR(20),"
                           "password VARCHAR(20),"
                           "nickname VARCHAR(20),"
                           "stunum VARCHAR(20))");
    if(success) {
        qDebug() << "数据库建立成功！";
    } else {
        qDebug() << "数据库建立失败！";
    }


}
xTcpServer::~xTcpServer() {
    db->close();
    delete db;
    delete clientPool;
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

    Worker * newWorker = new Worker(socketDescriptor);
    QThread *thread = new QThread();
    connect(thread,&QThread::started,newWorker,&Worker::initialize);
    connect(newWorker,&Worker::newTcpSocket,this,&xTcpServer::addSocket);
    connect(newWorker,&Worker::socketDisconnect,thread,&QThread::quit);
    connect(newWorker,&Worker::socketDisconnect,newWorker,&Worker::deleteLater);
    connect(newWorker,&Worker::socketWaitRemove,this,&xTcpServer::removeSocket);
//    connect(newWorker,&Worker::readMessage,this,&xTcpServer::messageController);
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
//void xTcpServer::messageController(QString const &message) {
//    qDebug() << "controller";
//    QStringList list = message.split("#");
//    QSqlQuery query;
//    if(list[0] == "login") {
//        qDebug() << "login";

//    } else if(list[0] == "register") {
//        QString str = QString("insert into user values (null,'%1','%2','%3','%4')").
//                arg(list[1]).arg(list[2]).arg(list[3]).arg(list[4]);
//        qDebug() << "register";
//        qDebug() << str;
//        if(query.exec(str)) {
//            qDebug() << "insert success!";

//        } else {
//            qDebug() << "insert failed!";
//        }
//    } else if(list[0] == "found") {
//        qDebug() << "found";
//    }

//}

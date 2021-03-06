#include "xtcpserver.h"
#include "synchapi.h"
#include "worker.h"
#include "xservertcpsocket.h"
xTcpServer::xTcpServer(QObject *parent) :
    QTcpServer(parent)
{
    clientPool = new QHash<int,xServerTcpSocket *>;
    onlineUser = new QHash<int,QString>;
    offlineUser = new QHash<QString,QStringList>;
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

    query.exec("select * from user");
    while(query.next()) {
        QStringList list;
        offlineUser->insert(query.value(1).toString(),list);
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
    broadcastList();
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
    connect(newWorker,&Worker::newLogin,this,&xTcpServer::newLogin);
    connect(this,&xTcpServer::offlineMessageList,newWorker,&Worker::sendOfflineMessage);
    connect(this,&xTcpServer::broadcastListSignal,newWorker,&Worker::broadcastUserList);
    connect(newWorker,&Worker::addOfflineMessage,this,&xTcpServer::insertOfflineMessage);

    newWorker->moveToThread(thread);
    thread->start();
}

void xTcpServer::addSocket(xServerTcpSocket *socket, int descriptor) {
    clientPool->insert(descriptor,socket);
}

void xTcpServer::removeSocket(int descriptor) {
    xServerTcpSocket *tcp = clientPool->value(descriptor);
    clientPool->remove(descriptor);
    QString username = onlineUser->value(descriptor);
    if(onlineUser->remove(descriptor)) {
        QStringList list;
        offlineUser->insert(username.split("#")[0],list);
        broadcastList();
    }
    delete tcp;
    qDebug() << "remove socket from pool";
    qDebug() << username.split("#")[0] + " is offline";
}

void xTcpServer::newLogin(int handle, const QString & username) {
    qDebug() << username << " is login!";
    QStringList list = offlineUser->value(username.split("#")[0]);
    qDebug() << username.split("#")[0] << "'s offline message is " + list.join("#");
    emit offlineMessageList(list.join("#"),username.split("#")[0]);
    offlineUser->remove(username.split("#")[0]);
    qDebug() << "offline user " + username.split("#")[0] + " is removed";
    onlineUser->insert(handle,username);
    broadcastList();
}

void xTcpServer::broadcastList() {
    qDebug() << "begin broadcast!";
    QString str = "userlist";
    auto begin = onlineUser->begin();
    auto end = onlineUser->end();
    while(begin!=end) {

        str += ("#" + begin.value());
        begin++;
    }
    qDebug() << str;
    emit broadcastListSignal(str);
    str = "offlinelist";
    auto nbegin = offlineUser->begin();
    auto nend = offlineUser->end();
    while(nbegin!=nend) {
        str += ("#" + nbegin.key());
        nbegin++;
    }
    qDebug() << str;
    Sleep(40);
    emit broadcastListSignal(str);
}

void xTcpServer::insertOfflineMessage(const QString &username, const QString &str) {
    QStringList list = offlineUser->value(username);
    list << str;
    qDebug() << "插入后的离线列表：" + list.join("#");
    offlineUser->insert(username,list);
}

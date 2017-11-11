#ifndef XTCPSERVER_H
#define XTCPSERVER_H
#define PORT 6666

#include <QTcpServer>
#include "xservertcpsocket.h"
#include <QHash>
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>


class xTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit xTcpServer(QObject *parent = 0);
    ~xTcpServer();
    void startServer();
signals:
    void listenStatusChange(const QString &status);
    void broadcastListSignal(const QString &listStr);
//    void newLogin(QString const &username,QString const &nickname,QString const &ip);
public slots:
    void addSocket(xServerTcpSocket *,int);
    void removeSocket(int);
    void newLogin(int,QString const &);
    //来自客户端的消息处理
//    void messageController(QString const &);
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    void broadcastList();
    QHash<int,xServerTcpSocket *> * clientPool;
    QSqlDatabase * db;
    QHash<int,QString> * onlineUser;

};

#endif // XTCPSERVER_H

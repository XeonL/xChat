#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(qintptr handle,QObject *parent = nullptr);
    explicit Worker(QString const &ip,QObject *parent = nullptr);
    ~Worker();
signals:
    void newMessage(QString const &);
    void offlineMessage(QString const &);
    void anotherUserIp(QString const &);
public slots:
    void initialize();
    void getMessage();
    void sendMessage(QString const &);
private:
    void connectMiss();
    bool isDisconnected = false;
    QTcpSocket *tcpSocket;
    QString anotherIp;
    qintptr descriptor;
    bool active;
};

#endif // WORKER_H

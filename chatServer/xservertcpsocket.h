#ifndef xServerTcpSocket_H
#define xServerTcpSocket_H

#include <QTcpSocket>
#include <QObject>
class xServerTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit xServerTcpSocket(QObject *parent = 0);

private:


signals:

};

#endif // xServerTcpSocket_H

#ifndef XCLIENTUDPSOCKET_H
#define XCLIENTUDPSOCKET_H

#include <QUdpSocket>
class xClientUdpSocket : public QUdpSocket
{
public:
    xClientUdpSocket(QObject *parent = 0);
};

#endif // XCLIENTUDPSOCKET_H

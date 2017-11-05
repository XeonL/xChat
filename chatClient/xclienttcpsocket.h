#ifndef XCLIENTTCPSOCKET_H
#define XCLIENTTCPSOCKET_H

#include <QTcpSocket>
class xClientTcpSocket : public QTcpSocket
{
public:
    xClientTcpSocket(QObject *parent = 0);

};

#endif // XCLIENTTCPSOCKET_H

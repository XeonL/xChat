#ifndef XSERVERTHREAD_H
#define XSERVERTHREAD_H
#include <QThread>

class xServerThread : public QThread
{
    Q_OBJECT
public:
    xServerThread();
    void run();
};

#endif // XSERVERTHREAD_H

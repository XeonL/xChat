#include "tcpserver.h"

tcpServer::tcpServer(QObject *parent) :
    QTcpServer(parent)
{
    this->listen(QHostAddress::Any,8888);
}
tcpServer::~tcpServer() {

}
void tcpServer::incomingConnection(qintptr handle) {
    ChatWindow *chat = new ChatWindow(handle);
//    QThread *thread = new QThread();
    chat->setAttribute(Qt::WA_DeleteOnClose);
//    connect(thread,&QThread::started,chat,&ChatWindow::initialize);
//    connect(chat,&ChatWindow::destroyed,thread,&QThread::quit);
    chat->show();
    chat->initialize();
//    chat->moveToThread(thread);
//    thread->start();
}

#include "userwindow.h"
#include "ui_userwindow.h"
#include <QThread>
UserWindow::UserWindow(xClientTcpSocket *socket,QWidget *parent) :
    QWidget(parent),tcpSocket(socket),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    userList = new QHash<QString,QString>();
    server = new tcpServer(this);
    connect(server,&tcpServer::newConnection,this,&UserWindow::newChatWindow1);
}

UserWindow::~UserWindow()
{
    delete ui;
}
void UserWindow::updateUserList(const QString &data) {
    QStringList list = data.split("#");
    int len = list.count()/2;
    userList->clear();
    ui->userList->clear();
    for(int i=1;i<=len;i+=2) {
        userList->insert(list[i],list[i+1].mid(7));
        ui->userList->addItem(list[i]);
    }
}

void UserWindow::on_chatbutton_clicked()
{
    QString user = ui->usernameToChat->text();
    QString ip = userList->value(user);
    if(ip=="") {
        QMessageBox::warning(nullptr,"Warning","请输入在线用户的用户名！",QMessageBox::Yes);
    } else {
        newChatWindow(user,ip);
    }
}

void UserWindow::updateInfo(const QString &name) {
    myName = name;
}

void UserWindow::newChatWindow1(qintptr descriptor) {
    Worker *newWorker = new Worker(descriptor);
    ChatWindow *newWindow = new ChatWindow(myName);
    newWindow->setAttribute(Qt::WA_DeleteOnClose);
    QThread *thread = new QThread();
    connect(thread,&QThread::started,newWorker,&Worker::initialize);
    connect(newWorker,&Worker::destroyed,thread,&QThread::quit);
    connect(newWindow,&ChatWindow::destroyed,newWorker,&Worker::deleteLater);
    connect(newWorker,&Worker::newMessage,newWindow,&ChatWindow::newMessageGet);
    connect(newWorker,&Worker::newMessage,newWindow,&ChatWindow::show);
    connect(newWindow,&ChatWindow::newMessageToSend,newWorker,&Worker::sendMessage);
    newWindow->show();
    newWorker->moveToThread(thread);
    thread->start();
}
void UserWindow::newChatWindow(QString const &user,QString const &ip) {
    Worker *newWorker = new Worker(ip);
    ChatWindow *newWindow = new ChatWindow(myName,user);
    newWindow->setAttribute(Qt::WA_DeleteOnClose);
    QThread *thread = new QThread();
    connect(thread,&QThread::started,newWorker,&Worker::initialize);
    connect(newWorker,&Worker::destroyed,thread,&QThread::quit);
    connect(newWindow,&ChatWindow::destroyed,newWorker,&Worker::deleteLater);
    connect(newWorker,&Worker::newMessage,newWindow,&ChatWindow::newMessageGet);
    connect(newWorker,&Worker::newMessage,newWindow,&ChatWindow::show);
    connect(newWindow,&ChatWindow::newMessageToSend,newWorker,&Worker::sendMessage);
    newWindow->show();
    newWorker->moveToThread(thread);
    thread->start();
}

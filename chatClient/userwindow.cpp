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
    qDebug() << data;
    QStringList list = data.split("#");
    int len = list.count()/2;
    userList->clear();
    ui->userList->clear();
    for(int i=1;i<=len;i++) {
        userList->insert(list[2*i-1],list[2*i].mid(7));
        ui->userList->addItem(list[2*i-1]);
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

void UserWindow::on_offlineMessageButton_clicked()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    QString str = QString("offline#");
    QString message = myName + " " + current_date + " " + ui->offlineMessage->text();
    str += ui->offlineUserName->text();
    str += "#";
    str += message;
    QByteArray block = str.toUtf8();
    tcpSocket->write(block);
    qDebug() << str;
}
void UserWindow::getOfflineMessage(const QString &str) {
    qDebug() << "获取离线消息表..";
    QStringList list = str.split("#");
    for(int i = 1;i < list.count();i++) {
        ui->offlineMessageList->addItem(list[i]);
    }
    qDebug() << str;
}
void UserWindow::updateOfflineList(const QString &data) {
    QStringList list = data.split("#");
    qDebug() << data << "..." << list.count();
    for(int i = 1;i < list.count();i++) {
        ui->offlineUserList->addItem(list[i]);
    }
}

#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(qintptr handle,QWidget *parent = 0);
    explicit ChatWindow(QString &username,QString &ip,QWidget *parent = 0);
    ~ChatWindow();
public slots:
    void initialize();
signals:
//    void sockDisconnectedSignal();
private slots:
    void on_sendMessageButton_clicked();
    void readMessage();

private:
    void sendChatMessage(QString const &);
    void sockDisConnect();
    Ui::ChatWindow *ui;
    QTcpSocket *tcpsocket;
    bool type;
    int handle;
    QString username;
    QString ip;
    bool sign;
};

#endif // CHATWINDOW_H

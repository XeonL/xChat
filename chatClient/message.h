#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>

namespace Ui {
class Message;
}

class Message : public QWidget
{
    Q_OBJECT

public:
    explicit Message(QWidget *parent = 0);
    ~Message();
    void setText(const QString &);

private:
    Ui::Message *ui;

};

#endif // MESSAGE_H

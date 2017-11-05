#ifndef FOUNDACCOUNTWINDOW_H
#define FOUNDACCOUNTWINDOW_H

#include <QWidget>
#include "xclienttcpsocket.h"

namespace Ui {
class FoundAccountWindow;
}

class FoundAccountWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FoundAccountWindow(xClientTcpSocket *, QWidget *parent = 0);
    ~FoundAccountWindow();
signals:
    void returnBack();
private slots:
    void on_back_clicked();

    void on_foundButton_clicked();

private:
    Ui::FoundAccountWindow *ui;
    xClientTcpSocket *myTcpSocket;
    void clear();
};

#endif // FOUNDACCOUNTWINDOW_H

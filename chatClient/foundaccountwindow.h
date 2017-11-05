#ifndef FOUNDACCOUNTWINDOW_H
#define FOUNDACCOUNTWINDOW_H

#include <QWidget>

namespace Ui {
class FoundAccountWindow;
}

class FoundAccountWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FoundAccountWindow(QWidget *parent = 0);
    ~FoundAccountWindow();

private:
    Ui::FoundAccountWindow *ui;
};

#endif // FOUNDACCOUNTWINDOW_H

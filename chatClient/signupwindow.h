#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = 0);
    ~SignupWindow();

private:
    Ui::SignupWindow *ui;
};

#endif // SIGNUPWINDOW_H

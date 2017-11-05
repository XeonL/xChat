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

private slots:
    void on_back_clicked();

    void on_signup_clicked();

signals:
    void returnBack();
private:
    Ui::SignupWindow *ui;
};

#endif // SIGNUPWINDOW_H

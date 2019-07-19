#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QWidget>
#include "ui_login_window.h"

class LoginWindow: public QWidget {
private:
    Ui::LoginWindow * ui;
public:
    LoginWindow() {
        ui = new Ui::LoginWindow;
        ui->setupUi(this);
    }
    ~LoginWindow() {
        delete ui;
    }
};

#endif // LOGIN_WINDOW_H

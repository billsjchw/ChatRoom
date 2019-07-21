#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include "ui_chat_window.h"

class ChatWindow: public QMainWindow {
    Q_OBJECT
private:
    Ui::ChatWindow * ui;
public:
    ChatWindow() {
        setAttribute(Qt::WA_DeleteOnClose);
        ui = new Ui::ChatWindow;
        ui->setupUi(this);
    }
    ~ChatWindow() {
        delete ui;
    }
protected:
    void closeEvent(QCloseEvent * event) {
        int choice = QMessageBox::question(this, "Logout", "Are you sure to logout?",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (choice == QMessageBox::Yes) {
            event->accept();
            emit finish();
        } else
            event->ignore();
    }
signals:
    void finish();
};

#endif // CHAT_WINDOW_H

#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "chat_window.h"
#include <QTcpSocket>
#include <QJsonObject>
#include "packet.h"
#include "packet_code.h"
#include "ui_login_window.h"

class LoginWindow: public QMainWindow {
    Q_OBJECT
private:
    Ui::LoginWindow * ui;
    ChatWindow * chatWindow;
    QTcpSocket socket;
    Packet packet;
public:
    LoginWindow() {
        ui = new Ui::LoginWindow;
        ui->setupUi(this);
        connect(ui->connect, SIGNAL(triggered(bool)), this, SLOT(connectToServer()));
        connect(ui->login, SIGNAL(clicked(bool)), this, SLOT(handleLogin()));
        connect(ui->regist, SIGNAL(clicked(bool)), this, SLOT(handleRegist()));
        connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError()));
    }
    ~LoginWindow() {
        delete ui;
    }
protected:
    void closeEvent(QCloseEvent * event) {
        socket.disconnectFromHost();
        if (socket.state() != QAbstractSocket::UnconnectedState)
            socket.waitForDisconnected();
        event->accept();
    }
private:
    QJsonObject makeLoginInfo(const QString & username, const QString & password) {
        QJsonObject info;
        info.insert("username", username);
        info.insert("password", password);
        return info;
    }
    void jumpToChatWindow() {
        chatWindow = new ChatWindow();
        connect(chatWindow, SIGNAL(finish()), this, SLOT(close()));
        hide();
        chatWindow->show();
    }
    void disableLogin() {
        ui->username->setEnabled(false);
        ui->password->setEnabled(false);
        ui->login->setEnabled(false);
        ui->regist->setEnabled(false);
    }
    void enableLogin() {
        ui->username->setEnabled(true);
        ui->password->setEnabled(true);
        ui->login->setEnabled(true);
        ui->regist->setEnabled(true);
    }
private slots:
    void connectToServer() {
        ui->connect->setEnabled(false);
        ui->hint->setText("Connecting...");
        ui->hint->setStyleSheet("color:black");
        socket.connectToHost("127.0.0.1", 8000);
        if (socket.waitForConnected()) {
            ui->hint->setText("Connect to the server successfully.");
            ui->hint->setStyleSheet("color:green");
            enableLogin();
        } else {
            ui->hint->setText("Fail to connect to the server.");
            ui->hint->setStyleSheet("color:red");
            ui->connect->setEnabled(true);
        }
    }
    void handleLogin() {
        disableLogin();
        QString username = ui->username->text();
        QString password = ui->password->text();
        packet.code = REQ_LOGIN;
        packet.content = makeLoginInfo(username, password);
        ui->hint->setText("Processing...");
        ui->hint->setStyleSheet("color:black");
        packet.send(socket);
        packet.receive(socket);
        if (packet.code == RET_LOGIN_SUC)
            jumpToChatWindow();
        else {
            enableLogin();
            ui->hint->setStyleSheet("color:red");
            switch (packet.code) {
            case RET_DUP_LOGIN:
                ui->hint->setText("User already logins."); break;
            case RET_WRONG_PWD:
                ui->hint->setText("Wrong password."); break;
            case RET_WRONG_USR:
                ui->hint->setText("User does not exist."); break;
            }
        }
    }
    void handleRegist() {
        disableLogin();
        QString username = ui->username->text();
        QString password = ui->password->text();
        packet.code = REQ_REGIST;
        packet.content = makeLoginInfo(username, password);
        ui->hint->setText("Processing...");
        ui->hint->setStyleSheet("color:black");
        packet.send(socket);
        packet.receive(socket);
        if (packet.code == RET_LOGIN_SUC)
            jumpToChatWindow();
        else {
            enableLogin();
            ui->hint->setStyleSheet("color:red");
            switch (packet.code) {
            case RET_DUP_USR:
                ui->hint->setText("User already exists."); break;
            }
        }
    }
    void handleSocketError() {
        QMessageBox::critical(this, "Network Error", "Lose the connection with the server.", QMessageBox::Abort);
        close();
    }
};

#endif // LOGIN_WINDOW_H

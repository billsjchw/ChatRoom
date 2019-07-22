#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include "personal_info_window.h"
#include <QThread>
#include <QTcpSocket>
#include "socket_handler.h"
#include "packet.h"
#include <QJsonObject>
#include <QDateTime>
#include <deque>
#include <QString>
#include "ui_chat_window.h"

class ChatWindow: public QMainWindow {
    Q_OBJECT
private:
    static const int msgListCapacity = 20;
private:
    Ui::ChatWindow * ui;
    bool socketError;
    SocketHandler socketHandler;
    QThread thread;
    std::deque<Packet> msgList;
    QString username;
public:
    ChatWindow(QTcpSocket * socket, QString username):
        socketHandler(socket), username(username) {
        setAttribute(Qt::WA_DeleteOnClose);
        ui = new Ui::ChatWindow;
        ui->setupUi(this);
        socketError = false;
        socketHandler.moveToThread(&thread);
        thread.start();
        connect(ui->logout, SIGNAL(triggered(bool)), this, SLOT(close()));
        connect(ui->sendTxtMsg, SIGNAL(clicked(bool)), this, SLOT(handleSendTxtMsg()));
        connect(ui->info, SIGNAL(triggered(bool)), this, SLOT(showPersonalInfo()));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError()));
        connect(&socketHandler, SIGNAL(newMsg(Packet)), this, SLOT(handleNewMsg(Packet)));
        connect(this, SIGNAL(packetToSend(Packet)), &socketHandler, SLOT(sendPacket(Packet)));
        emit socket->readyRead();
    }
    ~ChatWindow() {
        delete ui;
    }
protected:
    void closeEvent(QCloseEvent * event) {
        int choice;
        if (socketError)
            choice = QMessageBox::Yes;
        else
            choice = QMessageBox::question(this, "Logout", "Are you sure to logout?",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (choice == QMessageBox::Yes) {
            thread.quit();
            thread.wait();
            event->accept();
            emit finish();
        } else
            event->ignore();
    }
private:
    void updateMsgBrowser() {
        QString msgBrowserContent;
        for (int i = 0; i < msgList.size(); ++i) {
            switch (msgList[i].code) {
            case MSG_TXT:
                msgBrowserContent += makeTxtContent(msgList[i].content); break;
            case MSG_SYS:
                msgBrowserContent += makeSysContent(msgList[i].content); break;
            }
        }
        ui->msgBrowser->setText(msgBrowserContent);
    }
    QString makeTxtContent(QJsonObject msg) {
        QString sender = msg.take("sender").toString();
        QString content = msg.take("content").toString();
        return sender + ": " + content + "\n";
    }
    QString makeSysContent(QJsonObject msg) {
        QString content = msg.take("content").toString();
        return "[SYSTEM] " + content + "\n";
    }
signals:
    void finish();
    void packetToSend(Packet packet);
private slots:
    void handleSocketError() {
        socketError = true;
        QMessageBox::critical(this, "Network Error", "Lose connection with the server.", QMessageBox::Abort);
        close();
    }
    void handleNewMsg(Packet packet) {
        if (msgList.size() == msgListCapacity)
            msgList.pop_front();
        msgList.push_back(packet);
        updateMsgBrowser();
    }
    void handleSendTxtMsg() {
        QString sender = username;
        QString content = ui->msgEdit->toPlainText();
        QString sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        ui->msgEdit->setText("");
        QJsonObject msg;
        msg.insert("sender", sender);
        msg.insert("content", content);
        msg.insert("send_time", sendTime);
        emit packetToSend(Packet(MSG_TXT, msg));
    }
    void showPersonalInfo() {
        ui->info->setEnabled(false);
        PersonalInfoWindow * personalInfoWindow = new PersonalInfoWindow(this, username);
        connect(personalInfoWindow, SIGNAL(finish()), this, SLOT(enablePersonalInfo()));
        connect(&socketHandler, SIGNAL(setInfoResp(Packet)), personalInfoWindow, SLOT(notifySubmitFinish(Packet)));
        connect(personalInfoWindow, SIGNAL(packetToSend(Packet)), &socketHandler, SLOT(sendPacket(Packet)));
        personalInfoWindow->show();
    }
    void enablePersonalInfo() {
        ui->info->setEnabled(true);
    }
};

#endif // CHAT_WINDOW_H

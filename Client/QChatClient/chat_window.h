#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QKeyEvent>
#include <QCloseEvent>
#include "personal_info_window.h"
#include <QThread>
#include <QTcpSocket>
#include <QUrl>
#include "socket_handler.h"
#include "packet.h"
#include <QJsonObject>
#include <QDateTime>
#include <deque>
#include <map>
#include <QString>
#include <QStringList>
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
    PersonalInfoWindow * personalInfoWindow;
    std::deque<Packet> msgList;
    std::map<QString, QString> nicknameList;
    QString username;
    bool showNickname;
public:
    ChatWindow(QTcpSocket * socket, QString username):
        socketHandler(socket), username(username), showNickname(true) {
        setAttribute(Qt::WA_DeleteOnClose);
        ui = new Ui::ChatWindow;
        ui->setupUi(this);
        socketError = false;
        socketHandler.moveToThread(&thread);
        thread.start();
        personalInfoWindow = new PersonalInfoWindow(this, username);
        ui->msgBrowser->setOpenLinks(false);
        ui->msgBrowser->setOpenExternalLinks(false);
        connect(socket, SIGNAL(readyRead()), &socketHandler, SLOT(receivePacket()), Qt::QueuedConnection);
        connect(&socketHandler, SIGNAL(newMsg(Packet)), this, SLOT(handleNewMsg(Packet)));
        connect(&socketHandler, SIGNAL(setInfoResp(Packet)), personalInfoWindow, SLOT(notifySubmitFinish(Packet)));
        connect(&socketHandler, SIGNAL(basicInfoChange(Packet)), this, SLOT(handleBasicInfoChange(Packet)));
        connect(this, SIGNAL(packetToSend(Packet)), &socketHandler, SLOT(sendPacket(Packet)), Qt::QueuedConnection);
        connect(personalInfoWindow, SIGNAL(packetToSend(Packet)), &socketHandler, SLOT(sendPacket(Packet)));
        connect(ui->logout, SIGNAL(triggered(bool)), this, SLOT(close()));
        connect(ui->sendTxtMsg, SIGNAL(clicked(bool)), this, SLOT(handleSendTxtMsg()));
        connect(ui->info, SIGNAL(triggered(bool)), this, SLOT(showPersonalInfo()));
        connect(ui->usernameOrNickname, SIGNAL(triggered(bool)), this, SLOT(chooseNameKind()));
        connect(ui->msgBrowser, SIGNAL(anchorClicked(QUrl)), this, SLOT(handleUserInfoQry(QUrl)));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError()));
        emit socket->readyRead();
    }
    ~ChatWindow() {
        delete ui;
    }
protected:
    void keyPressEvent(QKeyEvent * event) {
        if (event->modifiers() == Qt::AltModifier && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return))
            handleSendTxtMsg();
    }
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
        ui->msgBrowser->setHtml(msgBrowserContent);
    }
    QString makeTxtContent(QJsonObject msg) {
        QString sender = msg.take("sender").toString();
        QString content = msg.take("content").toString();
        QString sendTime = msg.take("send_time").toString();
        QString senderName = sender;
        if (showNickname) {
            if (!nicknameList.count(sender)) {
                qDebug() << sender;
                nicknameList[sender] = sender;
                QJsonObject info;
                info.insert("username", sender);
                emit packetToSend(Packet(REQ_QRY_BASIC, info));
            }
            senderName = nicknameList[sender];
        }
        QString ret;
        ret += "<a href=\"" + sender + "\">" + senderName + "</a>";
        ret += "<font style=\"color:#2456CF\">" + plainToHtml(" " + sendTime) + "</font><br>";
        ret += "<font style=\"color:#000000\">" + plainToHtml("    " + content) + "</font><br>";
        return ret;
    }
    QString makeSysContent(QJsonObject msg) {
        QString content = msg.take("content").toString();
        return "<font style=\"color:#267F10\">" + plainToHtml("[SYSTEM] " + content) + "</font><br>";
    }
    QString plainToHtml(const QString & plain) {
        QString html = plain;
        html.replace("&", "&amp;");
        html.replace(" ", "&nbsp;");
        html.replace("<", "&lt;");
        html.replace(">", "&gt;");
        html.replace("\"", "&quot;");
        html.replace("'", "&apos;");
        html.replace("\n", "<br>");
        return html;
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
        personalInfoWindow->show();
    }
    void handleBasicInfoChange(Packet packet) {
        QJsonObject info = packet.content;
        QString username = info.take("username").toString();
        QString nickname = info.take("nickname").toString();
        nicknameList[username] = nickname;
        updateMsgBrowser();
    }
    void chooseNameKind() {
        QStringList choices;
        choices << "Username" << "Nickname";
        bool ok;
        QString choice = QInputDialog::getItem(this, "Show username/nickname", "Which one should be shown in the message box?",
                                               choices, showNickname, false, &ok);
        if (ok && showNickname != (choice == "Nickname")) {
            showNickname = choice == "Nickname";
            updateMsgBrowser();
        }
    }
    void handleUserInfoQry(QUrl username) {
        qDebug() << username;
    }
};

#endif // CHAT_WINDOW_H

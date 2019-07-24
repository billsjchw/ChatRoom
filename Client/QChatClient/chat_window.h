#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QKeyEvent>
#include <QCloseEvent>
#include "personal_info_window.h"
#include "user_info_window.h"
#include <QThread>
#include <QTcpSocket>
#include <QUrl>
#include "socket_handler.h"
#include "packet.h"
#include <QJsonObject>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <deque>
#include <map>
#include <utility>
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
    std::deque<Packet> msgList;
    std::map<QString, QString> nicknameList;
    QString username;
    QString path;
    bool showNickname;
    bool personalInfoWindowOn;
public:
    ChatWindow(QTcpSocket * socket, QString username):
        socketHandler(socket), username(username), showNickname(true), personalInfoWindowOn(false),
        path(QDir::homePath() + "/tmp/ChatRoom/" + username + "/pic_rcv/") {
        setAttribute(Qt::WA_DeleteOnClose);
        ui = new Ui::ChatWindow;
        ui->setupUi(this);
        QDir qDir;
        qDir.mkpath(path);
        socketError = false;
        socketHandler.moveToThread(&thread);
        thread.start();
        ui->msgBrowser->setOpenLinks(false);
        ui->msgBrowser->setOpenExternalLinks(false);
        connect(socket, SIGNAL(readyRead()), &socketHandler, SLOT(receivePacket()), Qt::QueuedConnection);
        connect(&socketHandler, SIGNAL(newMsg(Packet)), this, SLOT(handleNewMsg(Packet)));
        connect(&socketHandler, SIGNAL(basicUserInfo(Packet)), this, SLOT(handleBasicUserInfo(Packet)));
        connect(this, SIGNAL(packetToSend(Packet)), &socketHandler, SLOT(sendPacket(Packet)));
        connect(ui->logout, SIGNAL(triggered(bool)), this, SLOT(close()));
        connect(ui->sendTxtMsg, SIGNAL(clicked(bool)), this, SLOT(handleSendTxtMsg()));
        connect(ui->sendImgMsg, SIGNAL(clicked(bool)), this, SLOT(handleSendImgMsg()));
        connect(ui->info, SIGNAL(triggered(bool)), this, SLOT(showPersonalInfo()));
        connect(ui->usernameOrNickname, SIGNAL(triggered(bool)), this, SLOT(chooseNameKind()));
        connect(ui->msgBrowser, SIGNAL(anchorClicked(QUrl)), this, SLOT(handleUserInfoQuery(QUrl)));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError()));
        emit socket->readyRead();
    }
    ~ChatWindow() {
        delete ui;
        QDir qDir(path);
        QFileInfoList qFileInfoList = qDir.entryInfoList(QDir::Files);
        for (int i = 0; i < qFileInfoList.size(); ++i) {
            QFile imgFile(qFileInfoList[i].filePath());
            imgFile.remove();
        }
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
        QString msgBrowserContent = "<body>";
        for (int i = 0; i < msgList.size(); ++i) {
            switch (msgList[i].code) {
            case MSG_TXT:
                msgBrowserContent += makeTxtContent(msgList[i].content); break;
            case MSG_SYS:
                msgBrowserContent += makeSysContent(msgList[i].content); break;
            case MSG_IMG:
                msgBrowserContent += makeImgContent(msgList[i].content); break;
            }
        }
        msgBrowserContent += "</body>";
        ui->msgBrowser->setHtml(msgBrowserContent);
    }
    QString getSenderName(QString sender) {
        QString senderName = sender;
        if (showNickname) {
            if (!nicknameList.count(sender)) {
                nicknameList[sender] = sender;
                QJsonObject info;
                info.insert("username", sender);
                emit packetToSend(Packet(REQ_QRY_BASIC, info));
            }
            senderName = nicknameList[sender];
        }
        return senderName;
    }
    QString makeTxtContent(QJsonObject msg) {
        QString sender = msg.take("sender").toString();
        QString content = msg.take("content").toString();
        QString sendTime = msg.take("send_time").toString();
        QString senderName = getSenderName(sender);
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
    QString makeImgContent(QJsonObject msg) {
        QString sender = msg.take("sender").toString();
        QString filename = msg.take("content").toString();
        QString sendTime = msg.take("send_time").toString();
        QString senderName = getSenderName(sender);
        QString ret;
        ret += "<a href=\"" + sender + "\">" + senderName + "</a>";
        ret += "<font style=\"color:#2456CF\">" + plainToHtml(" " + sendTime) + "</font><br>";
        ret += plainToHtml("    ") + "<img src=\"" + filename + "\"/><br>";
        return ret;
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
        if (msgList.size() == msgListCapacity) {
            if (msgList.front().code == MSG_IMG) {
                QFile imgFile(msgList.front().content.take("content").toString());
                imgFile.remove();
            }
            msgList.pop_front();
        }
        if (packet.code == MSG_IMG) {
            QString content = packet.content.take("content").toString();
            QByteArray binary = QByteArray::fromBase64(content.toLocal8Bit());
            QImage img;
            img.loadFromData(binary, "JPG");
            QString filename = path + QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz") + ".jpg";
            img.save(filename, "JPG");
            packet.content.insert("content", filename);
        }
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
    void handleSendImgMsg() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "/home", "Images (*.jpg *.jpeg)");
        QImage img(fileName, "JPG");
        QByteArray binary;
        QBuffer buffer(&binary);
        buffer.open(QIODevice::WriteOnly);
        img.save(&buffer, "JPG");
        QString sender = username;
        QString content = QString::fromLocal8Bit(binary.toBase64());
        QString sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QJsonObject msg;
        msg.insert("sender", sender);
        msg.insert("content", content);
        msg.insert("send_time", sendTime);
        emit packetToSend(Packet(MSG_IMG, msg));
    }
    void showPersonalInfo() {
        if (personalInfoWindowOn)
            return;
        personalInfoWindowOn = true;
        PersonalInfoWindow * personalInfoWindow = new PersonalInfoWindow(this, username);
        connect(personalInfoWindow, SIGNAL(packetToSend(Packet)), &socketHandler, SLOT(sendPacket(Packet)));
        connect(&socketHandler, SIGNAL(detailUserInfo(Packet)), personalInfoWindow, SLOT(updatePersonalInfo(Packet)));
        connect(&socketHandler, SIGNAL(setInfoResp(Packet)), personalInfoWindow, SLOT(notifySubmitFinish(Packet)));
        connect(personalInfoWindow, SIGNAL(finish()), this, SLOT(personalInfoWindowOff()));
        QJsonObject info;
        info.insert("username", username);
        emit packetToSend(Packet(REQ_QRY_DETAIL, info));
        personalInfoWindow->show();
    }
    void handleBasicUserInfo(Packet packet) {
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
    void handleUserInfoQuery(QUrl url) {
        UserInfoWindow * userInfoWindow = new UserInfoWindow(this, url.toString());
        connect(&socketHandler, SIGNAL(detailUserInfo(Packet)), userInfoWindow, SLOT(updateUserInfo(Packet)));
        connect(userInfoWindow, SIGNAL(packetToSend(Packet)), &socketHandler, SLOT(sendPacket(Packet)));
        userInfoWindow->startQuery();
        userInfoWindow->show();
    }
    void personalInfoWindowOff() {
        personalInfoWindowOn = false;
    }
};

#endif // CHAT_WINDOW_H

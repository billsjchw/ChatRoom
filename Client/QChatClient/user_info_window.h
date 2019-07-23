#ifndef USER_INFO_WINDOW_H
#define USER_INFO_WINDOW_H

#include <QWidget>
#include <QTimerEvent>
#include "packet.h"
#include <QJsonObject>
#include <QString>
#include "ui_user_info_window.h"

class UserInfoWindow: public QWidget {
    Q_OBJECT
private:
    Ui::UserInfoWindow * ui;
    QString username;
    int timerId;
public:
    UserInfoWindow(QWidget * parent, QString username):
        username(username), timerId(0) {
        setParent(parent);
        setWindowFlag(Qt::Window);
        ui = new Ui::UserInfoWindow;
        ui->setupUi(this);
        ui->username->setText(username);
    }
    ~UserInfoWindow() {
        delete ui;
        killTimer(timerId);
    }
    void startQuery() {
        queryUserInfo();
        timerId = startTimer(10000);
    }
protected:
    void timerEvent(QTimerEvent * event) {
        if (event->timerId() == timerId)
            queryUserInfo();
    }
private:
    void queryUserInfo() {
        QJsonObject info;
        info.insert("username", username);
        emit packetToSend(Packet(REQ_QRY_DETAIL, info));
    }
signals:
    void packetToSend(Packet packet);
private slots:
    void updateUserInfo(Packet packet) {
        QJsonObject info = packet.content;
        if (info.take("username").toString() != username)
            return;
        ui->created->setText(info.take("created").toString());
        ui->nickname->setText(info.take("nickname").toString());
        ui->age->setText(info.take("age").toString());
        ui->gender->setText(info.take("gender").toString());
        ui->email->setText(info.take("email").toString());
    }
};

#endif // USER_INFO_WINDOW_H

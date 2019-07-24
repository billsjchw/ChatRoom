#ifndef PERSONAL_INFO_WINDOW_H
#define PERSONAL_INFO_WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QJsonObject>
#include "packet.h"
#include <QDateTime>
#include <QString>
#include "ui_personal_info_window.h"

class PersonalInfoWindow: public QMainWindow {
    Q_OBJECT
private:
    Ui::PersonalInfoWindow * ui;
    QString username;
    bool submitting;
    QString lastReqTime;
public:
    PersonalInfoWindow(QWidget * parent, QString username):
        username(username), submitting(false) {
        setParent(parent);
        setWindowFlag(Qt::Window);
        ui = new Ui::PersonalInfoWindow;
        ui->setupUi(this);
        ui->submit->hide();
        ui->username->setText(username);
        connect(ui->enableEdit, SIGNAL(triggered(bool)), this, SLOT(enableEdit()));
        connect(ui->submit, SIGNAL(clicked(bool)), this, SLOT(handleSubmit()));
    }
    ~PersonalInfoWindow() {
        delete ui;
    }
protected:
    void closeEvent(QCloseEvent * event) {
        event->accept();
        emit finish();
    }
private:
    void disableEdit() {
        ui->submit->hide();
        ui->hint->show();
        ui->nickname->setEnabled(false);
        ui->age->setEnabled(false);
        ui->gender->setEnabled(false);
        ui->email->setEnabled(false);
    }
signals:
    void packetToSend(Packet packet);
    void finish();
private slots:
    void enableEdit() {
        ui->submit->show();
        ui->hint->hide();
        ui->nickname->setEnabled(true);
        ui->age->setEnabled(true);
        ui->gender->setEnabled(true);
        ui->email->setEnabled(true);
    }
    void updatePersonalInfo(Packet packet) {
        QJsonObject info = packet.content;
        if (info.take("username").toString() != username ||
                !ui->submit->isHidden() || submitting)
            return;
        ui->created->setText(info.take("created").toString());
        ui->nickname->setText(info.take("nickname").toString());
        ui->age->setText(info.take("age").toString());
        ui->gender->setCurrentText(info.take("gender").toString());
        ui->email->setText(info.take("email").toString());
    }
    void handleSubmit() {
        disableEdit();
        QJsonObject request;
        QJsonObject info;
        info.insert("username", ui->username->text());
        info.insert("nickname", ui->nickname->text());
        info.insert("age", ui->age->text());
        info.insert("gender", ui->gender->currentText());
        info.insert("email", ui->email->text());
        lastReqTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
        request.insert("req_time", lastReqTime);
        request.insert("info", info);
        emit packetToSend(Packet(REQ_SET_INFO, request));
        ui->hint->setText("Submitting...");
        submitting = true;
    }
    void notifySubmitFinish(Packet packet) {
        QString reqTime = packet.content.take("req_time").toString();
        if (reqTime == lastReqTime) {
            submitting = false;
            ui->hint->setText("Submit successfully.");
        }
    }
};

#endif // PERSONAL_INFO_WINDOW_H

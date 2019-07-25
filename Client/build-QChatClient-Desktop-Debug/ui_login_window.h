/********************************************************************************
** Form generated from reading UI file 'login_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_WINDOW_H
#define UI_LOGIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QAction *connect;
    QWidget *centralwidget;
    QLineEdit *password;
    QLineEdit *username;
    QPushButton *regist;
    QLabel *label_2;
    QLabel *label;
    QPushButton *login;
    QLabel *hint;
    QMenuBar *menubar;
    QMenu *menuServer;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QStringLiteral("LoginWindow"));
        LoginWindow->resize(410, 241);
        connect = new QAction(LoginWindow);
        connect->setObjectName(QStringLiteral("connect"));
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        password = new QLineEdit(centralwidget);
        password->setObjectName(QStringLiteral("password"));
        password->setEnabled(false);
        password->setGeometry(QRect(190, 80, 113, 25));
        password->setEchoMode(QLineEdit::Password);
        username = new QLineEdit(centralwidget);
        username->setObjectName(QStringLiteral("username"));
        username->setEnabled(false);
        username->setGeometry(QRect(190, 30, 113, 25));
        regist = new QPushButton(centralwidget);
        regist->setObjectName(QStringLiteral("regist"));
        regist->setEnabled(false);
        regist->setGeometry(QRect(220, 130, 89, 25));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 80, 81, 17));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 30, 81, 17));
        login = new QPushButton(centralwidget);
        login->setObjectName(QStringLiteral("login"));
        login->setEnabled(false);
        login->setGeometry(QRect(90, 130, 89, 25));
        hint = new QLabel(centralwidget);
        hint->setObjectName(QStringLiteral("hint"));
        hint->setGeometry(QRect(90, 160, 301, 17));
        LoginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 410, 22));
        menuServer = new QMenu(menubar);
        menuServer->setObjectName(QStringLiteral("menuServer"));
        LoginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        LoginWindow->setStatusBar(statusbar);

        menubar->addAction(menuServer->menuAction());
        menuServer->addAction(connect);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "Chat Room", Q_NULLPTR));
        connect->setText(QApplication::translate("LoginWindow", "Connect", Q_NULLPTR));
        regist->setText(QApplication::translate("LoginWindow", "Register", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginWindow", "password", Q_NULLPTR));
        label->setText(QApplication::translate("LoginWindow", "username", Q_NULLPTR));
        login->setText(QApplication::translate("LoginWindow", "Login", Q_NULLPTR));
        hint->setText(QApplication::translate("LoginWindow", "<html><head/><body><p><span style=\" color:#ef2929;\">Connect to the server first.</span></p></body></html>", Q_NULLPTR));
        menuServer->setTitle(QApplication::translate("LoginWindow", "Server", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_WINDOW_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QPushButton *login;
    QPushButton *regist;
    QLineEdit *username;
    QLineEdit *password;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QStringLiteral("LoginWindow"));
        LoginWindow->resize(400, 300);
        login = new QPushButton(LoginWindow);
        login->setObjectName(QStringLiteral("login"));
        login->setGeometry(QRect(90, 170, 89, 25));
        regist = new QPushButton(LoginWindow);
        regist->setObjectName(QStringLiteral("regist"));
        regist->setGeometry(QRect(220, 170, 89, 25));
        username = new QLineEdit(LoginWindow);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(190, 70, 113, 25));
        password = new QLineEdit(LoginWindow);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(190, 120, 113, 25));
        label = new QLabel(LoginWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 70, 81, 17));
        label_2 = new QLabel(LoginWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 120, 81, 17));

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "Chat Room", Q_NULLPTR));
        login->setText(QApplication::translate("LoginWindow", "Login", Q_NULLPTR));
        regist->setText(QApplication::translate("LoginWindow", "Regist", Q_NULLPTR));
        label->setText(QApplication::translate("LoginWindow", "username", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginWindow", "password", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_WINDOW_H

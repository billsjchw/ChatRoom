/********************************************************************************
** Form generated from reading UI file 'user_info_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_INFO_WINDOW_H
#define UI_USER_INFO_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInfoWindow
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *username;
    QLabel *created;
    QLabel *nickname;
    QLabel *age;
    QLabel *gender;
    QLabel *email;

    void setupUi(QWidget *UserInfoWindow)
    {
        if (UserInfoWindow->objectName().isEmpty())
            UserInfoWindow->setObjectName(QStringLiteral("UserInfoWindow"));
        UserInfoWindow->resize(430, 420);
        label = new QLabel(UserInfoWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 70, 81, 17));
        label_2 = new QLabel(UserInfoWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 120, 101, 17));
        label_5 = new QLabel(UserInfoWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(96, 270, 61, 20));
        label_3 = new QLabel(UserInfoWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 170, 71, 17));
        label_4 = new QLabel(UserInfoWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(120, 220, 31, 17));
        label_6 = new QLabel(UserInfoWindow);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(105, 320, 41, 20));
        username = new QLabel(UserInfoWindow);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(220, 70, 131, 17));
        created = new QLabel(UserInfoWindow);
        created->setObjectName(QStringLiteral("created"));
        created->setGeometry(QRect(220, 120, 151, 17));
        nickname = new QLabel(UserInfoWindow);
        nickname->setObjectName(QStringLiteral("nickname"));
        nickname->setGeometry(QRect(220, 170, 131, 17));
        age = new QLabel(UserInfoWindow);
        age->setObjectName(QStringLiteral("age"));
        age->setGeometry(QRect(220, 220, 151, 17));
        gender = new QLabel(UserInfoWindow);
        gender->setObjectName(QStringLiteral("gender"));
        gender->setGeometry(QRect(220, 270, 161, 20));
        email = new QLabel(UserInfoWindow);
        email->setObjectName(QStringLiteral("email"));
        email->setGeometry(QRect(220, 320, 171, 20));

        retranslateUi(UserInfoWindow);

        QMetaObject::connectSlotsByName(UserInfoWindow);
    } // setupUi

    void retranslateUi(QWidget *UserInfoWindow)
    {
        UserInfoWindow->setWindowTitle(QApplication::translate("UserInfoWindow", "User Information", Q_NULLPTR));
        label->setText(QApplication::translate("UserInfoWindow", "username", Q_NULLPTR));
        label_2->setText(QApplication::translate("UserInfoWindow", "created time", Q_NULLPTR));
        label_5->setText(QApplication::translate("UserInfoWindow", "gender", Q_NULLPTR));
        label_3->setText(QApplication::translate("UserInfoWindow", "nickname", Q_NULLPTR));
        label_4->setText(QApplication::translate("UserInfoWindow", "age", Q_NULLPTR));
        label_6->setText(QApplication::translate("UserInfoWindow", "email", Q_NULLPTR));
        username->setText(QString());
        created->setText(QString());
        nickname->setText(QString());
        age->setText(QString());
        gender->setText(QString());
        email->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UserInfoWindow: public Ui_UserInfoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_INFO_WINDOW_H

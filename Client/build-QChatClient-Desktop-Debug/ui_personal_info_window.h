/********************************************************************************
** Form generated from reading UI file 'personal_info_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONAL_INFO_WINDOW_H
#define UI_PERSONAL_INFO_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
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

class Ui_PersonalInfoWindow
{
public:
    QAction *enableEdit;
    QWidget *centralwidget;
    QLineEdit *username;
    QLineEdit *created;
    QLineEdit *nickname;
    QLineEdit *age;
    QLineEdit *email;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *gender;
    QPushButton *submit;
    QLabel *hint;
    QMenuBar *menubar;
    QMenu *menuSetting;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PersonalInfoWindow)
    {
        if (PersonalInfoWindow->objectName().isEmpty())
            PersonalInfoWindow->setObjectName(QStringLiteral("PersonalInfoWindow"));
        PersonalInfoWindow->resize(461, 431);
        enableEdit = new QAction(PersonalInfoWindow);
        enableEdit->setObjectName(QStringLiteral("enableEdit"));
        centralwidget = new QWidget(PersonalInfoWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        username = new QLineEdit(centralwidget);
        username->setObjectName(QStringLiteral("username"));
        username->setEnabled(false);
        username->setGeometry(QRect(220, 40, 151, 25));
        created = new QLineEdit(centralwidget);
        created->setObjectName(QStringLiteral("created"));
        created->setEnabled(false);
        created->setGeometry(QRect(220, 90, 151, 25));
        nickname = new QLineEdit(centralwidget);
        nickname->setObjectName(QStringLiteral("nickname"));
        nickname->setEnabled(false);
        nickname->setGeometry(QRect(220, 140, 151, 25));
        age = new QLineEdit(centralwidget);
        age->setObjectName(QStringLiteral("age"));
        age->setEnabled(false);
        age->setGeometry(QRect(220, 190, 151, 25));
        age->setInputMethodHints(Qt::ImhNone);
        email = new QLineEdit(centralwidget);
        email->setObjectName(QStringLiteral("email"));
        email->setEnabled(false);
        email->setGeometry(QRect(220, 290, 151, 25));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 40, 81, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 90, 101, 17));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 140, 71, 17));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(150, 190, 31, 17));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(126, 240, 61, 20));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(135, 290, 41, 20));
        gender = new QComboBox(centralwidget);
        gender->setObjectName(QStringLiteral("gender"));
        gender->setEnabled(false);
        gender->setGeometry(QRect(220, 240, 151, 25));
        submit = new QPushButton(centralwidget);
        submit->setObjectName(QStringLiteral("submit"));
        submit->setEnabled(true);
        submit->setGeometry(QRect(182, 340, 89, 25));
        hint = new QLabel(centralwidget);
        hint->setObjectName(QStringLiteral("hint"));
        hint->setGeometry(QRect(117, 340, 221, 16));
        hint->setAlignment(Qt::AlignCenter);
        PersonalInfoWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PersonalInfoWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 461, 22));
        menuSetting = new QMenu(menubar);
        menuSetting->setObjectName(QStringLiteral("menuSetting"));
        PersonalInfoWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PersonalInfoWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        PersonalInfoWindow->setStatusBar(statusbar);

        menubar->addAction(menuSetting->menuAction());
        menuSetting->addAction(enableEdit);

        retranslateUi(PersonalInfoWindow);

        QMetaObject::connectSlotsByName(PersonalInfoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PersonalInfoWindow)
    {
        PersonalInfoWindow->setWindowTitle(QApplication::translate("PersonalInfoWindow", "Personal Information", Q_NULLPTR));
        enableEdit->setText(QApplication::translate("PersonalInfoWindow", "Enable Editing", Q_NULLPTR));
        label->setText(QApplication::translate("PersonalInfoWindow", "username", Q_NULLPTR));
        label_2->setText(QApplication::translate("PersonalInfoWindow", "created time", Q_NULLPTR));
        label_3->setText(QApplication::translate("PersonalInfoWindow", "nickname", Q_NULLPTR));
        label_4->setText(QApplication::translate("PersonalInfoWindow", "age", Q_NULLPTR));
        label_5->setText(QApplication::translate("PersonalInfoWindow", "gender", Q_NULLPTR));
        label_6->setText(QApplication::translate("PersonalInfoWindow", "email", Q_NULLPTR));
        gender->clear();
        gender->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("PersonalInfoWindow", "Male", Q_NULLPTR)
         << QApplication::translate("PersonalInfoWindow", "Female", Q_NULLPTR)
        );
        submit->setText(QApplication::translate("PersonalInfoWindow", "Submit", Q_NULLPTR));
        hint->setText(QString());
        menuSetting->setTitle(QApplication::translate("PersonalInfoWindow", "Edit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PersonalInfoWindow: public Ui_PersonalInfoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONAL_INFO_WINDOW_H

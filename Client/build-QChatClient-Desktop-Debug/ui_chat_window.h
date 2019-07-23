/********************************************************************************
** Form generated from reading UI file 'chat_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_WINDOW_H
#define UI_CHAT_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QAction *info;
    QAction *logout;
    QAction *usernameOrNickname;
    QWidget *centralwidget;
    QTextBrowser *msgBrowser;
    QTextEdit *msgEdit;
    QPushButton *sendTxtMsg;
    QPushButton *sendImgMsg;
    QMenuBar *menubar;
    QMenu *menuMore;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QStringLiteral("ChatWindow"));
        ChatWindow->resize(739, 545);
        info = new QAction(ChatWindow);
        info->setObjectName(QStringLiteral("info"));
        logout = new QAction(ChatWindow);
        logout->setObjectName(QStringLiteral("logout"));
        usernameOrNickname = new QAction(ChatWindow);
        usernameOrNickname->setObjectName(QStringLiteral("usernameOrNickname"));
        centralwidget = new QWidget(ChatWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        msgBrowser = new QTextBrowser(centralwidget);
        msgBrowser->setObjectName(QStringLiteral("msgBrowser"));
        msgBrowser->setGeometry(QRect(70, 20, 601, 361));
        msgEdit = new QTextEdit(centralwidget);
        msgEdit->setObjectName(QStringLiteral("msgEdit"));
        msgEdit->setGeometry(QRect(70, 390, 601, 70));
        sendTxtMsg = new QPushButton(centralwidget);
        sendTxtMsg->setObjectName(QStringLiteral("sendTxtMsg"));
        sendTxtMsg->setGeometry(QRect(580, 470, 89, 25));
        sendImgMsg = new QPushButton(centralwidget);
        sendImgMsg->setObjectName(QStringLiteral("sendImgMsg"));
        sendImgMsg->setGeometry(QRect(470, 470, 101, 25));
        ChatWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChatWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 739, 22));
        menuMore = new QMenu(menubar);
        menuMore->setObjectName(QStringLiteral("menuMore"));
        ChatWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ChatWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ChatWindow->setStatusBar(statusbar);

        menubar->addAction(menuMore->menuAction());
        menuMore->addAction(info);
        menuMore->addAction(usernameOrNickname);
        menuMore->addAction(logout);

        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChatWindow)
    {
        ChatWindow->setWindowTitle(QApplication::translate("ChatWindow", "Chat Room", Q_NULLPTR));
        info->setText(QApplication::translate("ChatWindow", "Personal information", Q_NULLPTR));
        logout->setText(QApplication::translate("ChatWindow", "Logout", Q_NULLPTR));
        usernameOrNickname->setText(QApplication::translate("ChatWindow", "Show username/nickname", Q_NULLPTR));
        sendTxtMsg->setText(QApplication::translate("ChatWindow", "Send", Q_NULLPTR));
        sendImgMsg->setText(QApplication::translate("ChatWindow", "Send Pictrue", Q_NULLPTR));
        menuMore->setTitle(QApplication::translate("ChatWindow", "More", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_WINDOW_H

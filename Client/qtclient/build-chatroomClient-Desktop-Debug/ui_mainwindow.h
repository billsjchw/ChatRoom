/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect_To_Server;
    QWidget *centralWidget;
    QTextBrowser *info_text;
    QPushButton *send_button;
    QTextEdit *input_text;
    QMenuBar *menuBar;
    QMenu *menuServer;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(321, 351);
        actionConnect_To_Server = new QAction(MainWindow);
        actionConnect_To_Server->setObjectName(QStringLiteral("actionConnect_To_Server"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        info_text = new QTextBrowser(centralWidget);
        info_text->setObjectName(QStringLiteral("info_text"));
        info_text->setGeometry(QRect(10, 10, 291, 151));
        send_button = new QPushButton(centralWidget);
        send_button->setObjectName(QStringLiteral("send_button"));
        send_button->setGeometry(QRect(10, 260, 81, 28));
        input_text = new QTextEdit(centralWidget);
        input_text->setObjectName(QStringLiteral("input_text"));
        input_text->setGeometry(QRect(10, 170, 291, 81));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 321, 22));
        menuServer = new QMenu(menuBar);
        menuServer->setObjectName(QStringLiteral("menuServer"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuServer->menuAction());
        menuServer->addAction(actionConnect_To_Server);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionConnect_To_Server->setText(QApplication::translate("MainWindow", "Connect To Server", Q_NULLPTR));
        send_button->setText(QApplication::translate("MainWindow", "SEND", Q_NULLPTR));
        menuServer->setTitle(QApplication::translate("MainWindow", "Server", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

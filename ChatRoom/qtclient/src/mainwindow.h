#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    chatClient *cl;

signals:
    void newMessageSent(const QString &);

private slots:
    void on_send_button_clicked();
    void on_actionConnect_To_Server_triggered();
    void add_new_msg(const QString&);
};

#endif // MAINWINDOW_H

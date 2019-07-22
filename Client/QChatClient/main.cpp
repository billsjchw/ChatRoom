#include <QApplication>
#include "login_window.h"
#include <QMetaType>
#include "packet.h"
#include <QAbstractSocket>

int main(int argc, char * argv[]) {
    QApplication ChatRoomApp(argc, argv);
    qRegisterMetaType<Packet>("Packet");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

    LoginWindow loginWindow;
    loginWindow.show();

    return ChatRoomApp.exec();
}

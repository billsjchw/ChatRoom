#include <QApplication>
#include "login_window.h"
#include <QMetaType>
#include "packet.h"

int main(int argc, char * argv[]) {
    QApplication ChatRoomApp(argc, argv);
    qRegisterMetaType<Packet>("Packet");

    LoginWindow loginWindow;
    loginWindow.show();

    return ChatRoomApp.exec();
}

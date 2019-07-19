#include <QApplication>
#include "login_window.h"

int main(int argc, char * argv[]) {
    QApplication ChatRoomApp(argc, argv);
    ChatRoomApp.setQuitOnLastWindowClosed(false);

    LoginWindow loginWindow;
    loginWindow.show();

    return ChatRoomApp.exec();
}

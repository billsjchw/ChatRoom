#ifndef SOCKET_THREAD_H
#define SOCKET_THREAD_H

#include <QTcpSocket>
#include <QThread>
#include "packet.h"

class SocketHandler: public QObject {
    Q_OBJECT
private:
    QTcpSocket * socket;
    Packet packet;
public:
    SocketHandler(QTcpSocket * socket) {
        socket->setParent(this);
        this->socket = socket;
        connect(socket, SIGNAL(readyRead()), this, SLOT(receivePacket()));
    }
signals:
    void newMsg(Packet packet);
private slots:
    void receivePacket() {
        while (socket->bytesAvailable()) {
            packet.receive(socket);
            switch (packet.code) {
            case MSG_TXT: case MSG_SYS:
                emit newMsg(packet); break;
            }
        }
    }
    void sendPacket(Packet packet) {
        packet.send(socket);
    }
};

#endif // SOCKET_THREAD_H

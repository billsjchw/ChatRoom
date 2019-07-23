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
    }
signals:
    void newMsg(Packet packet);
    void newImgMsg(Packet packet);
    void setInfoResp(Packet packet);
    void basicUserInfo(Packet packet);
    void detailUserInfo(Packet packet);
private slots:
    void receivePacket() {
        while (socket->bytesAvailable()) {
            packet.receive(socket);
            switch (packet.code) {
            case MSG_TXT: case MSG_SYS: case MSG_IMG:
                emit newMsg(packet); break;
            case RET_SET_INFO_SUC:
                emit setInfoResp(packet); break;
            case DATA_BASIC:
                emit basicUserInfo(packet); break;
            case DATA_DETAIL:
                emit detailUserInfo(packet); break;
            }
        }
    }
    void sendPacket(Packet packet) {
        packet.send(socket);
    }
};

#endif // SOCKET_THREAD_H

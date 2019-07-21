#ifndef PACKET_H
#define PACKET_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QTcpSocket>
#include <iostream>

class Packet: public QObject {
public:
    char code;
    QJsonObject content;
    void receive(QTcpSocket & socket) {
        QByteArray binary = readNByte(socket, 1);
        code = binary[0];
        binary = readNByte(socket, 4);
        uint32_t size = binaryToUint32(binary);
        binary = readNByte(socket, size);
        content = jsonToObject(binary);
    }
    void send(QTcpSocket & socket) {
        QByteArray binary;
        binary.append(code);
        QByteArray json = objToJson(content);
        uint32_t size = json.size();
        binary.append((char *) &size, 4);
        binary.append(json);
        socket.write(binary);
        socket.flush();
    }
private:
    static QByteArray objToJson(const QJsonObject & obj) {
        QJsonDocument doc(obj);
        return doc.toJson();
    }
    static QJsonObject jsonToObject(const QByteArray & json) {
        QJsonDocument doc = QJsonDocument::fromJson(json);
        return doc.object();
    }
    static QByteArray readNByte(QTcpSocket & socket, uint32_t n) {
        QByteArray binary;
        while (socket.bytesAvailable() < n)
            socket.waitForReadyRead(-1);
        char * buffer = new char[BUFSIZ];
        for (uint32_t left = n; left > 0; ) {
            int k = socket.read(buffer, std::min(left, uint32_t(BUFSIZ)));
            binary.append(buffer, k);
            left -= k;
        }
        delete buffer;
        return binary;
    }
    static uint32_t binaryToUint32(const QByteArray & binary) {
        uint32_t ret = 0;
        for (int i = 0; i < 4; ++i)
            ret += (uint32_t) binary[i] << i;
        return ret;
    }
};

#endif // PACKET_H
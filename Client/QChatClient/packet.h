#ifndef PACKET_H
#define PACKET_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>

class Packet {
public:
    char code;
    QJsonObject content;
    bool receive(QTcpSocket socket) {
        std::pair<QByteArray, bool> ret;
        ret = readNByte(socket, 1);
        if (!ret.second)
            return false;
        code = ret.first[0];
        ret = readNByte(socket, 4);
        if (!ret.second)
            return false;
        uint32_t size = binaryToUint32(ret.first);
        ret = readNByte(socket, size);
        if (!ret.second)
            return false;
        content = jsonToObject(ret.first);
    }
    bool send(QTcpSocket socket) {
        QByteArray binary;
        binary.append(code);
        QByteArray json = objToJson(content);
        uint32_t size = json.size();
        binary.append((char *) &size, 4);
        binary.append(json);
        return socket.write(binary) != -1;
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
    static std::pair<QByteArray, bool> readNByte(QTcpSocket socket, uint32_t n) {
        QByteArray binary;
        char * buffer = new char[BUFSIZ];
        for (uint32_t left = n; left > 0; ) {
            k = socket.read(buffer, std::min(BUFSIZ, left));
            if (k == -1)
                return std::make_pair(QByteArray(), false);
            binary.append(buffer, k);
            left -= k;
        }
        delete buffer;
        return std::make_pair(binary, true);
    }
    static uint32_t binaryToUint32(const QByteArray & binary) {
        uint32_t ret = 0;
        for (int i = 0; i < 4; ++i)
            ret += (uint32_t) binary[i] << i;
        return ret;
    }
};

#endif // PACKET_H

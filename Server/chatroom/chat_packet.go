package chatroom

import (
	"encoding/binary"
	"net"
)

const (
	NULL = byte(iota)
	REQ_LOGIN
	REQ_REGIST
	REQ_SET_INFO
	REQ_QRY_BASIC
	REQ_QRY_DETAIL
	MSG_TXT
	MSG_IMG
	MSG_SYS
	DATA_BASIC
	DATA_DETAIL
	RET_DUP_USR
	RET_DUP_LOGIN
	RET_WRONG_PWD
	RET_WRONG_USR
	RET_LOGIN_SUC
	RET_SET_INFO_SUC
)

type Packet struct {
	Code    byte
	Content []byte
}

func NewPacket(code byte, content []byte) *Packet {
	packet := new(Packet)
	packet.Code = code
	packet.Content = content
	return packet
}

func SendPacket(client net.Conn, packet *Packet) error {
	size := uint32(len(packet.Content))
	buffer := make([]byte, 5)
	buffer[0] = packet.Code
	binary.LittleEndian.PutUint32(buffer[1:5], size)
	buffer = append(buffer, packet.Content...)
	_, err := client.Write(buffer)
	return err
}

func RcvPacket(client net.Conn) (*Packet, error) {
	packet := new(Packet)
	buffer, err := readByte(client, 1)
	if err != nil {
		return nil, err
	}
	packet.Code = buffer[0]
	buffer, err = readByte(client, 4)
	if err != nil {
		return nil, err
	}
	size := binary.LittleEndian.Uint32(buffer)
	packet.Content, err = readByte(client, size)
	if err != nil {
		return nil, err
	}
	return packet, nil
}

func readByte(client net.Conn, size uint32) ([]byte, error) {
	buffer := make([]byte, size)
	for i := uint32(0); i < size; {
		slice := buffer[i:size]
		n, err := client.Read(slice)
		if err != nil {
			return nil, err
		}
		i += uint32(n)
	}
	return buffer, nil
}

package chatroom

import (
	"net"
	"time"
)

const BUFSIZE = 1024
const TIMEOUT = 10 * time.Second

const (
	USER_SEND_MSG = byte(0x00)
)

const (
	SERV_BCST_MSG = byte(0x00)
	SERV_USER_NAM = byte(0x01)
)

type Data struct {
	code    byte
	args    uint
	size    []uint
	content [][]byte
}

func rcvData(client net.Conn) (*Data, error) {
	data := new(Data)
	raw, err := readByte(client, 1)
	if err != nil {
		return nil, err
	}
	data.code = raw[0]
	raw, err = readByte(client, 4)
	if err != nil {
		return nil, err
	}
	data.args = byteStreamToInt(raw)
	for i := uint(0); i < data.args; i++ {
		raw, err = readByte(client, 4)
		if err != nil {
			return nil, err
		}
		data.size[i] = byteStreamToInt(raw)
	}
	for i := uint(0); i < data.args; i++ {
		data.content[i], err = readByte(client, data.size[i])
		if err != nil {
			return nil, err
		}
	}
	return data, nil
}

func sendData(client net.Conn, data *Data) error {
	var raw []byte
	raw = append(raw, data.code)
	raw = append(raw, intToByteStream(data.args)...)
	for i := uint(0); i < data.args; i++ {
		raw = append(raw, intToByteStream(data.size[i])...)
	}
	for i := uint(0); i < data.args; i++ {
		raw = append(raw, data.content[i]...)
	}
	client.Write(raw)
	return nil
}

func readByte(client net.Conn, size uint) ([]byte, error) {
	var buffer []byte
	var raw []byte
	for size > 0 {
		if size > BUFSIZE {
			buffer = make([]byte, BUFSIZE)
		} else {
			buffer = make([]byte, size)
		}
		readSize, err := client.Read(buffer)
		if err != nil {
			return nil, err
		}
		size -= uint(readSize)
		raw = append(raw, buffer...)
	}
	return raw, nil
}

func byteStreamToInt(buffer []byte) uint {
	ret := uint(0)
	for i := 0; i < 4; i++ {
		ret += uint(buffer[i]) << uint(i*8)
	}
	return ret
}

func intToByteStream(data uint) []byte {
	buffer := make([]byte, 4)
	for i := 0; i < 4; i++ {
		buffer[i] = byte((data >> uint(i*8)) & 0xFF)
	}
	return buffer
}

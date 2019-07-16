package chatroom

import (
	"net"
	"time"
)

const BUFSIZE = 1024
const TIMEOUT = 10 * time.Second

const (
	USER_SET_NAME = byte(0x00)
	USER_SEND_MSG = byte(0x01)
)

const (
	SERV_BCST_MSG = byte(0x00)
	SERV_DUP_NAME = byte(0x01)
	SERV_NEW_USER = byte(0x02)
	SERV_PROP_NAM = byte(0x03)
)

type Data struct {
	Code    byte
	Args    uint
	Size    []uint
	Content [][]byte
}

func NewData(code byte, content ...[]byte) *Data {
	data := new(Data)
	data.Code = code
	data.Args = uint(len(content))
	data.Size = make([]uint, data.Args)
	for i := uint(0); i < data.Args; i++ {
		data.Size[i] = uint(len(content[i]))
	}
	data.Content = content
	return data
}

func RcvData(client net.Conn) (*Data, error) {
	data := new(Data)
	raw, err := readByte(client, 1)
	if err != nil {
		return nil, err
	}
	data.Code = raw[0]
	raw, err = readByte(client, 4)
	if err != nil {
		return nil, err
	}
	data.Args = byteStreamToInt(raw)
	// PrintClientMsg("receive data from " + client.RemoteAddr().String() + ", Code=" +
	// 	strconv.Itoa(int(data.Code)) + ", Args=" + strconv.Itoa(int(data.Args)))
	data.Size = make([]uint, data.Args)
	for i := uint(0); i < data.Args; i++ {
		raw, err = readByte(client, 4)
		if err != nil {
			return nil, err
		}
		data.Size[i] = byteStreamToInt(raw)
	}
	data.Content = make([][]byte, data.Args)
	for i := uint(0); i < data.Args; i++ {
		data.Content[i], err = readByte(client, data.Size[i])
		if err != nil {
			return nil, err
		}
	}
	return data, nil
}

func SendData(client net.Conn, data *Data) error {
	var raw []byte
	raw = append(raw, data.Code)
	raw = append(raw, intToByteStream(data.Args)...)
	for i := uint(0); i < data.Args; i++ {
		raw = append(raw, intToByteStream(data.Size[i])...)
	}
	for i := uint(0); i < data.Args; i++ {
		raw = append(raw, data.Content[i]...)
	}
	client.Write(raw)
	return nil
}

func readByte(client net.Conn, Size uint) ([]byte, error) {
	var buffer []byte
	var raw []byte
	for Size > 0 {
		if Size > BUFSIZE {
			buffer = make([]byte, BUFSIZE)
		} else {
			buffer = make([]byte, Size)
		}
		readSize, err := client.Read(buffer)
		if err != nil {
			return nil, err
		}
		Size -= uint(readSize)
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

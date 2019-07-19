package chatroom

import (
	"bufio"
	"encoding/json"
	"fmt"
	"io"
	"net"
	"strconv"
)

type ChatClient struct {
	addr     string
	conn     net.Conn
	updMsg   chan *Packet
	updBasic chan *Packet
	begQry   chan *QryRequest
	stopQry  chan *QryRequest
	in       io.Reader
	out      io.Writer
}

type QryRequest struct {
	username string
	dataChan chan *User
}

func NewChatClient(addr string, port int, in io.Reader, out io.Writer) *ChatClient {
	client := new(ChatClient)
	client.addr = addr + ":" + strconv.Itoa(port)
	client.in = in
	client.out = out
	client.updMsg = make(chan *Packet)
	client.updBasic = make(chan *Packet)
	client.begQry = make(chan *QryRequest)
	client.stopQry = make(chan *QryRequest)
	return client
}

func (client *ChatClient) Start() {
	client.conn, _ = net.Dial("tcp", client.addr)
	defer client.conn.Close()
	lineScan := bufio.NewScanner(client.in)
	code := NULL
	var username string
	for code != RET_LOGIN_SUC {
		fmt.Fprintf(client.out, "%s", "Registe or login? [r/l] ")
		var choice string
		fmt.Fscan(client.in, &choice)
		fmt.Fprintf(client.out, "%s", "username: ")
		fmt.Fscan(client.in, &username)
		fmt.Fprintf(client.out, "%s", "password: ")
		var password string
		fmt.Fscan(client.in, &password)
		content, _ := json.Marshal(newUser(username, password))
		switch choice {
		case "r":
			SendPacket(client.conn, NewPacket(REQ_REGIST, content))
		case "l":
			SendPacket(client.conn, NewPacket(REQ_LOGIN, content))
		}
		resp, _ := RcvPacket(client.conn)
		code = resp.Code
		switch code {
		case RET_DUP_USR:
			fmt.Fprintln(client.out, "[SYSTEM] User "+username+" already exists.")
		case RET_DUP_LOGIN:
			fmt.Fprintln(client.out, "[SYSTEM] User "+username+" already logins.")
		case RET_WRONG_PWD:
			fmt.Fprintln(client.out, "[SYSTEM] Wrong Password.")
		case RET_WRONG_USR:
			fmt.Fprintln(client.out, "[SYSTEM] User "+username+" does not exist.")
		}
	}
	fmt.Fprintln(client.out, "[SYSTEM] You login successfully.")
	quit := make(chan struct{})
	go client.getPacket()
	go client.control(quit)
	var cmd string
	for {
		fmt.Fscan(client.in, &cmd)
		switch cmd {
		case "SEND":
			lineScan.Scan()
			txt := lineScan.Text()
			msg := newMessage(username, txt, GetCurrentTimeString())
			content, _ := json.Marshal(msg)
			SendPacket(client.conn, NewPacket(MSG_TXT, content))
		case "LOGOUT":
			quit <- struct{}{}
			return
		}
	}
}

func (client *ChatClient) getPacket() {
	for {
		packet, err := RcvPacket(client.conn)
		if err != nil {
			return
		}
		switch packet.Code {
		case MSG_TXT, MSG_IMG, MSG_SYS:
			client.updMsg <- packet
		case DATA_BASIC:
			client.updBasic <- packet
		}
	}
}

func (client *ChatClient) control(quit chan struct{}) {
	quit_msg := make(chan struct{})
	go client.showMsg(quit_msg)
	for {
		select {
		case <-quit:
			quit_msg <- struct{}{}
			return
		}
	}
}

func (client *ChatClient) showMsg(quit chan struct{}) {
	nickname := make(map[string]string)
	for {
		select {
		case packet := <-client.updMsg:
			msg := jsonToMessage(packet.Content)
			switch packet.Code {
			case MSG_TXT:
				if _, flag := nickname[msg.Sender]; !flag {
					nickname[msg.Sender] = msg.Sender
				}
				fmt.Fprintln(client.out, nickname[msg.Sender]+": "+msg.Content)
			case MSG_SYS:
				fmt.Fprintln(client.out, "[SYSTEM] "+msg.Content)
			}
		case packet := <-client.updBasic:
			basic := jsonToUser(packet.Content)
			nickname[basic.Username] = basic.Nickname
		case <-quit:
			return
		}
	}
}

// func (client *ChatClient) showInfo() {
// }

func newQryRequest(username string, dataChan chan *User) {
	req := new(QryRequest)
	req.username = username
	req.dataChan = dataChan
}

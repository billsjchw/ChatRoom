package chatroom

import (
	"database/sql"
	"encoding/json"
	"net"
	"strconv"
)

type ChatServer struct {
	addr      string
	db        *sql.DB
	broadcast chan *Packet
	login     chan *LogRequest
	regist    chan *LogRequest
	leave     chan string
}

type SysMsg struct {
	Content string `json:"content,omitempty"`
}

type LogRequest struct {
	user  *User
	ret   chan byte
	input chan *Packet
}

func NewChatServer(addr string, port int, dbName string) *ChatServer {
	server := new(ChatServer)
	server.addr = addr + ":" + strconv.Itoa(port)
	server.db = openDatabase(dbName)
	server.broadcast = make(chan *Packet)
	server.login = make(chan *LogRequest)
	server.regist = make(chan *LogRequest)
	server.leave = make(chan string)
	return server
}

func (server *ChatServer) Start() {
	listener, err := net.Listen("tcp", server.addr)
	if err != nil {
		PrintErr(err.Error())
		return
	} else {
		PrintLog("start listening " + server.addr)
	}
	go server.handlePublic()
	for {
		client, err := listener.Accept()
		if err != nil {
			PrintErr(err.Error())
			return
		} else {
			PrintClientMsg("receive connection from " + client.RemoteAddr().String())
			go server.handleClient(client)
		}
	}
}

func (server *ChatServer) handlePublic() {
	online := make(map[string]chan *Packet)
	for {
		select {
		case packet := <-server.broadcast:
			for _, input := range online {
				input <- packet
			}
		case req := <-server.login:
			if _, flag := online[req.user.Username]; flag {
				req.ret <- DUPLICATE_LOGIN
				break
			}
			code := server.checkLogin(req.user.Username, req.user.Password)
			if code == SUCCESS {
				online[req.user.Username] = req.input
			}
			req.ret <- code
		case req := <-server.regist:
			code := server.handleRegist(req.user)
			if code == SUCCESS {
				online[req.user.Username] = req.input
			}
			req.ret <- code
		case username := <-server.leave:
			close(online[username])
			delete(online, username)
		}
	}
}

func (server *ChatServer) handleClient(client net.Conn) {
	input := make(chan *Packet)
	defer func() {
		client.Close()
		PrintClientMsg("connection " + client.RemoteAddr().String() + " closes")
	}()
	var user *User
	code := NULL
	for code != SUCCESS {
		packet, err := RcvPacket(client)
		if err != nil {
			return
		}
		user = newUser(packet.Content)
		ret := make(chan byte)
		switch packet.Code {
		case LOGIN:
			server.login <- newLogRequest(user, ret, input)
			code = <-ret
		case REGIST:
			server.regist <- newLogRequest(user, ret, input)
			code = <-ret
		}
		err = SendPacket(client, NewPacket(code, nil))
		if err != nil {
			return
		}
	}
	content, _ := json.Marshal(newSysMsg("User " + user.Username + " enters the chat room."))
	server.broadcast <- NewPacket(SYSTEM_MESSAGE, content)
	go writeClient(client, input)
	for {
		packet, err := RcvPacket(client)
		if err != nil {
			server.leave <- user.Username
			content, _ := json.Marshal(newSysMsg("User " + user.Username + " leaves the chat room."))
			server.broadcast <- NewPacket(SYSTEM_MESSAGE, content)
			return
		}
		switch packet.Code {
		case MESSAGE:
			server.broadcast <- NewPacket(USER_MESSAGE, packet.Content)
		}
	}
}

func writeClient(client net.Conn, input chan *Packet) {
	for packet := range input {
		err := SendPacket(client, packet)
		if err != nil {
			client.Close()
			break
		}
	}
	for range input {
	}
}

func (server *ChatServer) checkLogin(username string, password string) byte {
	right, exist := query(server.db, username, "password")
	if !exist {
		return WRONG_USERNAME
	}
	if password != right {
		return WRONG_PASSWORD
	}
	return SUCCESS
}

func (server *ChatServer) handleRegist(user *User) byte {
	exist := insert(server.db, user)
	if exist {
		return DUPLICATE_USERNAME
	}
	return SUCCESS
}

func newSysMsg(content string) *SysMsg {
	msg := new(SysMsg)
	msg.Content = content
	return msg
}

func newLogRequest(user *User, ret chan byte, input chan *Packet) *LogRequest {
	req := new(LogRequest)
	req.user = user
	req.ret = ret
	req.input = input
	return req
}

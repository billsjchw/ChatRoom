package chatroom

import (
	"database/sql"
	"encoding/json"
	"net"
	"reflect"
	"strconv"
	"strings"
)

type ChatServer struct {
	addr      string
	db        *sql.DB
	broadcast chan *Packet
	login     chan *LogRequest
	regist    chan *LogRequest
	leave     chan string
}

type LogRequest struct {
	user    *User
	ret     chan byte
	cliChan chan *Packet
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
			for _, cliChan := range online {
				cliChan <- packet
			}
		case req := <-server.login:
			if _, flag := online[req.user.Username]; flag {
				req.ret <- RET_DUP_LOGIN
				break
			}
			code := server.checkLogin(req.user.Username, req.user.Password)
			if code == RET_LOGIN_SUC {
				online[req.user.Username] = req.cliChan
			}
			req.ret <- code
		case req := <-server.regist:
			code := server.handleRegist(req.user.Username, req.user.Password)
			if code == RET_LOGIN_SUC {
				online[req.user.Username] = req.cliChan
			}
			req.ret <- code
		case username := <-server.leave:
			close(online[username])
			delete(online, username)
		}
	}
}

func (server *ChatServer) handleClient(client net.Conn) {
	cliChan := make(chan *Packet)
	defer func() {
		client.Close()
		PrintClientMsg("connection from " + client.RemoteAddr().String() + " closes")
	}()
	var username string
	code := NULL
	for code != RET_LOGIN_SUC {
		packet, err := RcvPacket(client)
		if err != nil {
			return
		}
		user := jsonToUser(packet.Content)
		username = user.Username
		ret := make(chan byte)
		switch packet.Code {
		case REQ_LOGIN:
			server.login <- newLogRequest(user, ret, cliChan)
			code = <-ret
		case REQ_REGIST:
			server.regist <- newLogRequest(user, ret, cliChan)
			code = <-ret
		}
		err = SendPacket(client, NewPacket(code, nil))
		if err != nil {
			return
		}
	}
	content, _ := json.Marshal(enterMsg(username))
	server.broadcast <- NewPacket(MSG_SYS, content)
	go writeClient(client, cliChan)
	for {
		packet, err := RcvPacket(client)
		if err != nil {
			server.leave <- username
			content, _ := json.Marshal(leaveMsg(username))
			server.broadcast <- NewPacket(MSG_SYS, content)
			return
		}
		switch packet.Code {
		case MSG_TXT, MSG_IMG:
			server.broadcast <- packet
		case REQ_SET_INFO:
			req := jsonToSetInfoReq(packet.Content)
			user := &req.Info
			server.setInfo(user)
			resp := newSetInfoResp(req.ReqTime)
			content, _ := json.Marshal(resp)
			cliChan <- NewPacket(RET_SET_INFO_SUC, content)
			basic := detailToBasic(user)
			content, _ = json.Marshal(basic)
			server.broadcast <- NewPacket(DATA_BASIC, content)
		case REQ_QRY_BASIC:
			username := jsonToUser(packet.Content).Username
			user := server.basicInfo(username)
			content, _ := json.Marshal(user)
			cliChan <- NewPacket(DATA_BASIC, content)
		case REQ_QRY_DETAIL:
			username := jsonToUser(packet.Content).Username
			user := server.detailInfo(username)
			content, _ := json.Marshal(user)
			cliChan <- NewPacket(DATA_DETAIL, content)
		}
	}
}

func writeClient(client net.Conn, cliChan chan *Packet) {
	for packet := range cliChan {
		err := SendPacket(client, packet)
		if err != nil {
			client.Close()
			break
		}
	}
	for range cliChan {
	}
}

func (server *ChatServer) checkLogin(username string, password string) byte {
	right, exist := query(server.db, username, "password")
	if !exist {
		return RET_WRONG_USR
	}
	if password != right {
		return RET_WRONG_PWD
	}
	return RET_LOGIN_SUC
}

func (server *ChatServer) handleRegist(username string, password string) byte {
	exist := insert(server.db, username, password)
	if exist {
		return RET_DUP_USR
	}
	return RET_LOGIN_SUC
}

func (server *ChatServer) setInfo(user *User) {
	username := user.Username
	userType := reflect.TypeOf(user).Elem()
	userVal := reflect.ValueOf(user).Elem()
	for i := 0; i < userType.NumField(); i++ {
		tag := strings.Split(userType.Field(i).Tag.Get("json"), ",")[0]
		value := userVal.Field(i).String()
		if tag != "username" && tag != "created" && tag != "password" {
			modify(server.db, username, tag, value)
		}
	}
}

func (server *ChatServer) basicInfo(username string) *User {
	user := new(User)
	user.Username = username
	user.Nickname, _ = query(server.db, username, "nickname")
	return user
}

func (server *ChatServer) detailInfo(username string) *User {
	user := new(User)
	userType := reflect.TypeOf(user).Elem()
	userVal := reflect.ValueOf(user).Elem()
	for i := 0; i < userType.NumField(); i++ {
		tag := strings.Split(userType.Field(i).Tag.Get("json"), ",")[0]
		value, _ := query(server.db, username, tag)
		userVal.Field(i).SetString(value)
	}
	return user
}

func newLogRequest(user *User, ret chan byte, cliChan chan *Packet) *LogRequest {
	req := new(LogRequest)
	req.user = user
	req.ret = ret
	req.cliChan = cliChan
	return req
}

func enterMsg(username string) *Message {
	content := "User " + username + " enters the chat room."
	msg := newMessage("system", content, GetCurrentTimeString())
	return msg
}

func leaveMsg(username string) *Message {
	content := "User " + username + " leaves the chat room."
	msg := newMessage("system", content, GetCurrentTimeString())
	return msg
}

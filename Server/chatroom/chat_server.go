package chatroom

import (
	"net"
	"strconv"
	"sync"
)

type User struct {
	conn net.Conn
	name string
}

type ChatServer struct {
	listenAddr string
	listener   net.Listener
	userlist   map[int]*User
	userCnt    int
	mux        sync.Mutex
}

func NewChatServer(addr string, port int) *ChatServer {
	server := new(ChatServer)
	server.listenAddr = addr + ":" + strconv.Itoa(port)
	server.userlist = make(map[int]*User)
	return server
}

func (server *ChatServer) StartListen() {
	listener, err := net.Listen("tcp", server.listenAddr)
	server.listener = listener
	if err != nil {
		PrintErr(err.Error())
		return
	} else {
		PrintLog("Start Listen " + server.listenAddr)
	}
	for {
		client, err := server.listener.Accept()
		if err != nil {
			PrintErr(err.Error())
			return
		} else {
			userID := server.newUser(client)
			go server.handle(userID)
		}
	}
}

func (server *ChatServer) handle(userID int) {
	server.mux.Lock()
	user := server.userlist[userID]
	server.mux.Unlock()
	client := user.conn
	defer func() {
		PrintErr(client.RemoteAddr().String() + " fail")
		server.mux.Lock()
		delete(server.userlist, userID)
		server.mux.Unlock()
		client.Close()
	}()
	err := server.sendUserName(userID)
	if err != nil {
		return
	}
	for {
		data, err := rcvData(client)
		if err != nil {
			return
		}
		switch data.code {
		case USER_SEND_MSG:
			go server.broadcast(data)
		}
	}
}

func (server *ChatServer) newUser(client net.Conn) int {
	user := new(User)
	user.conn = client
	server.mux.Lock()
	server.userCnt++
	user.name = "user" + strconv.Itoa(server.userCnt)
	userID := server.userCnt
	server.userlist[userID] = user
	server.mux.Unlock()
	PrintClientMsg("receive connection from " + client.RemoteAddr().String())
	return userID
}

func (server *ChatServer) sendUserName(userID int) error {
	server.mux.Lock()
	user := server.userlist[userID]
	name := user.name
	server.mux.Unlock()
	client := user.conn
	data := new(Data)
	data.code = SERV_USER_NAM
	data.args = uint(1)
	data.size = make([]uint, 1)
	data.size[0] = uint(len(name))
	data.content = make([][]byte, 1)
	data.content[0] = []byte(name)
	err := sendData(client, data)
	return err
}

func (server *ChatServer) broadcast(data *Data) {
	var clientList []net.Conn
	server.mux.Lock()
	for _, user := range server.userlist {
		clientList = append(clientList, user.conn)
	}
	server.mux.Unlock()
	bcst_data := *data
	bcst_data.code = SERV_BCST_MSG
	var wg sync.WaitGroup
	for _, client := range clientList {
		wg.Add(1)
		go func(client net.Conn) {
			sendData(client, &bcst_data)
			wg.Done()
		}(client)
	}
	wg.Wait()
}

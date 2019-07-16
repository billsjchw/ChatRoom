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
	namelist   map[string]bool
	mux        sync.Mutex
}

func NewChatServer(addr string, port int) *ChatServer {
	server := new(ChatServer)
	server.listenAddr = addr + ":" + strconv.Itoa(port)
	server.userlist = make(map[int]*User)
	server.namelist = make(map[string]bool)
	return server
}

func (server *ChatServer) StartListen() {
	listener, err := net.Listen("tcp", server.listenAddr)
	server.listener = listener
	if err != nil {
		PrintErr(err.Error())
		return
	} else {
		PrintLog("start listening " + server.listenAddr)
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
		PrintClientMsg(client.RemoteAddr().String() + " exits")
		server.mux.Lock()
		delete(server.namelist, user.name)
		delete(server.userlist, userID)
		server.mux.Unlock()
		client.Close()
	}()
	err := server.askForName(userID)
	if err != nil {
		return
	}
	for {
		data, err := RcvData(client)
		if err != nil {
			return
		}
		switch data.Code {
		case USER_SEND_MSG:
			PrintClientMsg("receive msg from " + client.RemoteAddr().String() + ", Content=\"" +
				string(data.Content[0]) + "\"")
			server.broadcast(userID, data)
		}
	}
}

func (server *ChatServer) newUser(client net.Conn) int {
	user := new(User)
	user.conn = client
	server.mux.Lock()
	server.userCnt++
	userID := server.userCnt
	server.userlist[userID] = user
	server.mux.Unlock()
	PrintClientMsg("receive connection from " + client.RemoteAddr().String())
	return userID
}

func (server *ChatServer) broadcast(userID int, data *Data) {
	var clientList []net.Conn
	server.mux.Lock()
	for k, user := range server.userlist {
		if k == userID {
			continue
		}
		clientList = append(clientList, user.conn)
	}
	user := server.userlist[userID]
	name := user.name
	server.mux.Unlock()
	content := data.Content
	content = append(content, []byte(name))
	bcst_data := NewData(SERV_BCST_MSG, content...)
	var wg sync.WaitGroup
	for _, client := range clientList {
		wg.Add(1)
		go func(client net.Conn) {
			SendData(client, bcst_data)
			wg.Done()
		}(client)
	}
	wg.Wait()
}

func (server *ChatServer) askForName(userID int) error {
	server.mux.Lock()
	user := server.userlist[userID]
	server.mux.Unlock()
	client := user.conn
	for {
		data, err := RcvData(client)
		if err != nil {
			return err
		}
		name := string(data.Content[0])
		server.mux.Lock()
		duplicate := server.namelist[name]
		server.namelist[name] = true
		server.mux.Unlock()
		if duplicate {
			server.notifyDupName(userID)
		} else {
			server.mux.Lock()
			user.name = name
			server.mux.Unlock()
			server.notifyPropName(userID)
			server.notifyNewUser(userID)
			break
		}
	}
	return nil
}

func (server *ChatServer) notifyDupName(userID int) {
	server.mux.Lock()
	client := server.userlist[userID].conn
	server.mux.Unlock()
	data := NewData(SERV_DUP_NAME)
	SendData(client, data)
}

func (server *ChatServer) notifyNewUser(userID int) {
	var clientList []net.Conn
	server.mux.Lock()
	for _, user := range server.userlist {
		clientList = append(clientList, user.conn)
	}
	user := server.userlist[userID]
	name := user.name
	server.mux.Unlock()
	data := NewData(SERV_NEW_USER, []byte(name))
	var wg sync.WaitGroup
	for _, client := range clientList {
		wg.Add(1)
		go func(client net.Conn) {
			SendData(client, data)
			wg.Done()
		}(client)
	}
	wg.Wait()
}

func (server *ChatServer) notifyPropName(userID int) {
	server.mux.Lock()
	client := server.userlist[userID].conn
	server.mux.Unlock()
	data := NewData(SERV_PROP_NAM)
	SendData(client, data)
}

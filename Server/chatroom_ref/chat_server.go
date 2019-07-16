package chatroom_ref

import (
	"net"
	"strconv"
)

const (
	LISTEN_TCP = "tcp"
	PING_MSG   = "receive connection from "
)

//data structure of server
type ChatServer struct {
	listenAddr string
	status     bool
	listener   net.Listener
}

//create a new server, you should explain why we do this
func NewChatServer(addr string, port int) *ChatServer {
	server := new(ChatServer)
	server.listenAddr = addr + ":" + strconv.Itoa(port)
	return server
}

//main server function
func (server ChatServer) StartListen() {
	//start listen on the address given
	listener, err := net.Listen(LISTEN_TCP, server.listenAddr)
	server.listener = listener

	//exit when server listen fail
	if err != nil {
		PrintErr(err.Error())
	} else {
		PrintLog("Start Listen " + server.listenAddr)
	}

	//main server loop, you should explain how this server loop works
	for {
		client, acceptError := server.listener.Accept() //when a user comes in
		if acceptError != nil {
			PrintErr(acceptError.Error()) //if accept go wrong, then the server will exit
			break
		} else {
			go server.userHandler(client) //then create a coroutine go process the user (What is coroutine? What's the function of keyword 'go'?)
		}
	}
}

func (server ChatServer) userHandler(client net.Conn) {
	buffer := make([]byte, 1024)      //create a buffer
	clientAddr := client.RemoteAddr() //get user's address
	var msg string
	PrintClientMsg(PING_MSG + clientAddr.String()) //print a log to show that a new client comes in
	for {                                          //main serve loop
		readSize, readError := client.Read(buffer) //why we can put a read in for loop?
		if readError != nil {
			PrintErr(clientAddr.String() + " fail") //if read error occurs, close the connection with user
			client.Close()
			break
		} else {
			msg = string(buffer[0:readSize])                //or convert the byte stream to a string
			PrintClientMsg(clientAddr.String() + ":" + msg) //then print the message
			client.Write(buffer[0:readSize])                //send the msg back to user
		}
	}
}

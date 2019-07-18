package main

import (
	"chatroom"
	"encoding/json"
	"fmt"
	"net"
)

type Data struct {
	Username string `json:"username"`
	Password string `json:"password"`
}

var finish chan struct{}

var listener net.Listener

func main() {
	listener, _ = net.Listen("tcp", "127.0.0.1:8000")
	go listen()
	conn, _ := net.Dial("tcp", "127.0.0.1:8000")
	data := Data{"billsjc", "12345678"}
	content, _ := json.Marshal(data)
	chatroom.SendPacket(conn, chatroom.LOGIN, content)
	<-finish
}

func listen() {
	client, _ := listener.Accept()
	defer client.Close()
	for {
		code, content, _ := chatroom.RcvPacket(client)
		fmt.Println(code, string(content))
	}
	finish <- struct{}{}
}

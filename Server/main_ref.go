package main

import (
	"chatroom_ref"
)

func main() {
	server := chatroom_ref.NewChatServer("127.0.0.1", 6666)
	server.StartListen()
}

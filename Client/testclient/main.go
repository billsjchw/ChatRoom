package main

import (
	"chatroom"
	"os"
)

func main() {
	client := chatroom.NewChatClient("127.0.0.1", 8000, os.Stdin, os.Stdout)
	client.Start()
}

package main

import (
	"bufio"
	"chatroom"
	"encoding/json"
	"fmt"
	"net"
	"os"
	"time"
)

type Message struct {
	Sender   string `json:"sender,omitempty"`
	Category string `json:"category,omitempty"`
	Content  string `json:"content,omitempty"`
	SendTime string `json:"send_time,omitempty"`
}

var conn net.Conn

func main() {
	conn, _ = net.Dial("tcp", "127.0.0.1:8000")
	defer conn.Close()
	user := new(chatroom.User)
	code := chatroom.NULL
	for code != chatroom.SUCCESS {
		fmt.Printf("%s", "Registe or Login? [r/l] ")
		var choice string
		fmt.Scan(&choice)
		fmt.Printf("%s", "username: ")
		fmt.Scan(&user.Username)
		fmt.Printf("%s", "password: ")
		fmt.Scan(&user.Password)
		content, _ := json.Marshal(user)
		if choice == "r" {
			chatroom.SendPacket(conn, chatroom.NewPacket(chatroom.REGIST, content))
		} else if choice == "l" {
			chatroom.SendPacket(conn, chatroom.NewPacket(chatroom.LOGIN, content))
		}
		resp, _ := chatroom.RcvPacket(conn)
		code = resp.Code
		switch code {
		case chatroom.SUCCESS:
			fmt.Println("[SYS] You login successfully.")
		case chatroom.DUPLICATE_LOGIN:
			fmt.Println("[SYS] User " + user.Username + " already logins.")
		case chatroom.WRONG_USERNAME:
			fmt.Println("[SYS] User " + user.Username + " does not exist.")
		case chatroom.WRONG_PASSWORD:
			fmt.Println("[SYS] Wrong password.")
		case chatroom.DUPLICATE_USERNAME:
			fmt.Println("[SYS] User " + user.Username + " already exists.")
		}
	}
	go handleResp()
	lineScanner := bufio.NewScanner(os.Stdin)
	for {
		var cmd string
		fmt.Scan(&cmd)
		switch cmd {
		case "SEND":
			lineScanner.Scan()
			text := lineScanner.Text()
			content, _ := json.Marshal(newMessage(user.Username, "text", text, time.Now().Format("2006/01/02 15:04:05")))
			chatroom.SendPacket(conn, chatroom.NewPacket(chatroom.MESSAGE, content))
		}
	}
}

func handleResp() {
	for {
		packet, _ := chatroom.RcvPacket(conn)
		switch packet.Code {
		case chatroom.SYSTEM_MESSAGE:
			var msg chatroom.SysMsg
			json.Unmarshal(packet.Content, &msg)
			fmt.Println("[SYS] " + msg.Content)
		case chatroom.USER_MESSAGE:
			var msg Message
			json.Unmarshal(packet.Content, &msg)
			if msg.Category == "text" {
				fmt.Println(msg.Sender + ": " + msg.Content)
			}
		}
	}
}

func newMessage(sender string, category string, content string, sendTime string) *Message {
	msg := new(Message)
	msg.Sender = sender
	msg.Category = category
	msg.Content = content
	msg.SendTime = sendTime
	return msg
}

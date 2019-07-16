package main

import (
	"bufio"
	"chatroom"
	"fmt"
	"net"
	"os"
	"sync"
)

var username string
var mux sync.Mutex

func main() {
	conn, _ := net.Dial("tcp", "127.0.0.1:8000")
	input := bufio.NewScanner(os.Stdin)
	duplicate := true
	for duplicate {
		fmt.Printf("%s", "username: ")
		input.Scan()
		username = input.Text()
		data := chatroom.NewData(chatroom.USER_SET_NAME, []byte(username))
		chatroom.SendData(conn, data)
		for {
			data, _ := chatroom.RcvData(conn)
			if data.Code == chatroom.SERV_DUP_NAME {
				fmt.Println("[SYS] Username " + username + " already exists.")
				break
			} else if data.Code == chatroom.SERV_PROP_NAM {
				duplicate = false
				break
			}
		}
	}
	go handleResp(conn)
	for {
		var cmd, msg string
		fmt.Scan(&cmd)
		switch cmd {
		case "SEND":
			input.Scan()
			msg = input.Text()
			fmt.Println("[MSG] " + username + ": " + msg)
			sendMsg(conn, msg)
		}
	}
}

func sendMsg(conn net.Conn, msg string) {
	data := chatroom.NewData(chatroom.USER_SEND_MSG, []byte(msg))
	chatroom.SendData(conn, data)
}

func handleResp(conn net.Conn) {
	for {
		data, _ := chatroom.RcvData(conn)
		switch data.Code {
		case chatroom.SERV_BCST_MSG:
			rcvBroadcast(data)
		case chatroom.SERV_NEW_USER:
			notifyNewUser(data)
		}
	}
}

func rcvBroadcast(data *chatroom.Data) {
	sender := string(data.Content[1])
	msg := string(data.Content[0])
	fmt.Println("[MSG] " + sender + ": " + msg)
}

func notifyNewUser(data *chatroom.Data) {
	name := string(data.Content[0])
	fmt.Println("[SYS] User " + name + " enters the chat room")
}

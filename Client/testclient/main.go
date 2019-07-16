package main

import (
	"fmt"
	"net"
	"sync"
)

var username string
var mux sync.Mutex

func main() {
	conn, err := net.Dial("tcp", "127.0.0.1:6666")
	if err != nil {
		return
	}
	for {
		var cmd, msg string
		fmt.Scan(&cmd)
		switch cmd {
		case "SEND":
			fmt.Scanln(&msg)
		}
	}
}

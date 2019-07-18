package main

import (
	"encoding/json"
	"fmt"
	"time"
)

type Message struct {
	Username string    `json:"username"`
	Content  []byte    `json:"content"`
	Time     time.Time `json:"time"`
}

func main() {
	msg := new(Message)
	msg.Username = "billsjc"
	msg.Content = []byte("Hello, everyone")
	msg.Time = time.Now()
	p, _ := json.Marshal(msg)
	// msg2 := new(Message)
	// json.Unmarshal(p, &msg2)
	fmt.Println(string(p))
}

package chatroom

import "encoding/json"

type Message struct {
	Sender   string `json:"sender,omitempty"`
	Content  string `json:"content,omitempty"`
	SendTime string `json:"send_time,omitempty"`
}

func jsonToMessage(content []byte) *Message {
	msg := new(Message)
	json.Unmarshal(content, msg)
	return msg
}

func newMessage(sender string, content string, sendTime string) *Message {
	msg := new(Message)
	msg.Sender = sender
	msg.Content = content
	msg.SendTime = sendTime
	return msg
}

type User struct {
	Username string `json:"username,omitempty"`
	Password string `json:"password,omitempty"`
	Created  string `json:"created,omitempty"`
	Nickname string `json:"nickname,omitempty"`
	Age      string `json:"age,omitempty"`
	Gender   string `json:"gender,omitempty"`
	Email    string `json:"email,omitempty"`
}

func jsonToUser(content []byte) *User {
	user := new(User)
	json.Unmarshal(content, user)
	return user
}

func detailToBasic(detail *User) *User {
	basic := new(User)
	basic.Username = detail.Username
	basic.Nickname = detail.Nickname
	return basic
}

func newUser(username string, password string) *User {
	user := new(User)
	user.Username = username
	user.Password = password
	return user
}

package chatroom

import (
	"database/sql"
	"encoding/json"
	"time"

	_ "github.com/mattn/go-sqlite3"
)

type User struct {
	Username string `json:"username,omitempty"`
	Password string `json:"password,omitempty"`
	Created  string `json:"created,omitempty"`
	Nickname string `json:"nickname,omitempty"`
	Age      string `json:"age,omitempty"`
	Gender   string `json:"gender,omitempty"`
	Email    string `json:"email,omitempty"`
}

func newUser(content []byte) *User {
	user := new(User)
	json.Unmarshal(content, user)
	return user
}

func openDatabase(dbName string) *sql.DB {
	db, _ := sql.Open("sqlite3", dbName)
	create := `
		CREATE TABLE IF NOT EXISTS userlist
		(
			username VARCHAR(64) PRIMARY KEY,
			password VARCHAR(64) NULL,
			created  VARCHAR(64) NULL,
			nickname VARCHAR(64) NULL,
			age      VARCHAR(16) NULL,
			gender   VARCHAR(16) NULL,
			email    VARCHAR(64) NULL
		)
	`
	db.Exec(create)
	return db
}

func query(db *sql.DB, username string, key string) (string, bool) {
	stmt, _ := db.Prepare("SELECT " + key + " FROM userlist WHERE username=?")
	row, _ := stmt.Query(username)
	stmt.Close()
	if !row.Next() {
		return "", false
	}
	var result string
	row.Scan(&result)
	row.Close()
	return result, true
}

func insert(db *sql.DB, user *User) bool {
	_, exist := query(db, user.Username, "username")
	if exist {
		return true
	}
	user.Created = time.Now().Format("2006/01/02 15:04:05")
	stmt, _ := db.Prepare("INSERT INTO userlist VALUES(?,?,?,?,?,?,?)")
	stmt.Exec(user.Username, user.Password, user.Created, user.Nickname,
		user.Age, user.Gender, user.Email)
	stmt.Close()
	return false
}

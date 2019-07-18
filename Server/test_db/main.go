package main

import (
	"database/sql"
	"fmt"

	_ "github.com/mattn/go-sqlite3"
)

func main() {
	db, _ := sql.Open("sqlite3", "./user.db")
	create := `
	CREATE TABLE IF NOT EXISTS userinfo
	(
		username VARCHAR(64) PRIMARY KEY,
		password VARCHAR(64) NULL,
		nickname VARCHAR(64) NULL
	)
	`
	db.Exec(create)
	insert, _ := db.Prepare("INSERT INTO userinfo(username, password, nickname) VALUES(?, ?, ?)")
	insert.Exec("billsjc", "1234abcd", "bill")
	insert.Exec("someone", "aaaaaaaa", "user")
	insert.Close()
	update, _ := db.Prepare("UPDATE userinfo SET nickname=? WHERE username=?")
	update.Exec("tom", "someone")
	update.Close()
	rows, _ := db.Query("SELECT * FROM userinfo")
	var username, password, nickname string
	for rows.Next() {
		rows.Scan(&username, &password, &nickname)
		fmt.Printf("username=%s, password=%s, nickname=%s\n", username, password, nickname)
	}
	db.Close()
}

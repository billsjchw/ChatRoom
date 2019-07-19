package chatroom

import (
	"database/sql"

	_ "github.com/mattn/go-sqlite3"
)

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

func query(db *sql.DB, username string, tag string) (string, bool) {
	stmt, _ := db.Prepare("SELECT " + tag + " FROM userlist WHERE username=?")
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

func insert(db *sql.DB, username string, password string) bool {
	_, exist := query(db, username, "username")
	if exist {
		return true
	}
	created := GetCurrentTimeString()
	nickname := username
	stmt, _ := db.Prepare("INSERT INTO userlist(username,password,created,nickname) VALUES(?,?,?,?)")
	stmt.Exec(username, password, created, nickname)
	stmt.Close()
	return false
}

func modify(db *sql.DB, username string, tag string, value string) {
	stmt, _ := db.Prepare("UPDATE userinfo SET " + tag + "=? WHERE username=?")
	stmt.Exec(value, username)
	stmt.Close()
}

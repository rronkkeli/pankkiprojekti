const mysql = require('mysql2');

const conn = mysql.createPool({
    host: 'localhost',
    user: 'testuser',
    password: 'testpwd',
    database: 'testdb'
});

module.exports = conn;
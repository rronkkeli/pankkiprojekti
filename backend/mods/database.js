const mysql = require('mysql2');

const conn = mysql.createPool({
    host: '127.0.0.1',
    user: 'bankadmin',
    password: 'bankadminpassword',
    database: 'bank'
});

module.exports = conn;
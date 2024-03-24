const mysql = require('mysql2');

const conn = mysql.createPool({
    host: 'localhost',
    user: 'bankadmin',
    password: 'bankadminpassword',
    database: 'bank'
});

module.exports = conn;
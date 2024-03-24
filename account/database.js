const mysql = require('mysql2');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'root',
  password: 'admin',
  database: 'bank'
});
module.exports = connection;
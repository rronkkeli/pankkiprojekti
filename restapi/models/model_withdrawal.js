const db = require('../mods/database');

withdrawal = {
    getAll: (account, callback) => {
        let sql = 'SELECT * FROM withdrawal WHERE idaccount=? ORDER BY timestamp DESC';
        db.query(sql, [account], callback);
    },

    add: (account, withdrawal, callback) => {
        let sql = 'INSERT INTO withdrawal VALUES (NULL, ?, ?, NOW())';
        db.query(sql, [account, withdrawal.amount], callback);
    },

    update: (withdrawal, callback) => {
        let sql = 'UPDATE withdrawal SET idaccount=?, amount=?, timestamp=? WHERE idwithdrawal=?';
        db.query(sql, [withdrawal.account, withdrawal.amount, withdrawal.timestamp, withdrawal.id], callback);
    },

    delete: (id, callback) => {
        let sql = 'DELETE FROM withdrawal WHERE idwithdrawal=?';
        db.query(sql, [id], callback);
    }
};

module.exports = withdrawal;
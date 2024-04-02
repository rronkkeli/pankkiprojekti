const db = require('../mods/database');

const account = {
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from account where idaccount=?', [id], callback);
  },
  add: function(account, callback) {
    return db.query(
      'insert into account (balance,credit) values(?,?)',
      [account.balance, account.credit],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from account where idaccount=?', [id], callback);
  },
  update: function(id, account, callback) {
    return db.query(
      'update account set balance=?,credit=? where idaccount=?',
      [account.balance, account.credit, id],
      callback
    );
  }
};
module.exports = account;
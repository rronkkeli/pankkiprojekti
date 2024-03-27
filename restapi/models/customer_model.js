const db = require('../mods/database');

const customer = {
  getAll: function(callback) {
    return db.query('select * from customer', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from customer where idcustomer=?', [id], callback);
  },
  add: function(customer, callback) {
    return db.query(
      'insert into customer (fname,lname,phone_number,birthdate, address) values(?,?,?,?,?)',
      [customer.fname,customer.lname, customer.phone_number, customer.birthdate, customer.address],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from customer where idcustomer=?', [id], callback);
  },
  update: function(id, customer, callback) {
    return db.query(
      'update customer set fname=?,lname=?, phone_number=?, birthdate=?, address=? where idcustomer=?',
      [customer.fname,customer.lname, customer.phone_number, customer.birthdate, customer.address, id],
      callback
    );
  }
};
module.exports = customer;
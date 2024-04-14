const db = require('../mods/database');

const tilitiedot = {
    getWithdrawakees: function(asiakas, callback) {
      return db.query('CALL tilitiedot(?)', [asiakas], callback);
    }
  };
  
  module.exports = tilitiedot;

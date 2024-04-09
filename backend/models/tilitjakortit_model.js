const db = require('../mods/database');

const tilitjakortit = {
    getAccountsAndCards: function(asiakas, callback) {
      return db.query('CALL tilit_ja_kortit(?)', [asiakas], callback);
    }
  };
  
  module.exports = tilitjakortit;

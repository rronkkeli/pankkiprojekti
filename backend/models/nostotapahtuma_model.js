const db = require('../mods/database');

const nostotapahtuma  = {
    getMoneyOut: function(asiakas, tili_numero, nosto, callback) {
      return db.query('CALL nostotapahtuma(?,?,?)', [asiakas, tili_numero, nosto], callback);
    }
  };
  
  module.exports = nostotapahtuma ;

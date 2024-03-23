const db = require('../database');
const bcrypt=require('bcryptjs');

const credentials={

    getOneCredentials(idcustomer, callback){
        return db.query("SELECT * FROM credentials WHERE idcustomer=?",[idcustomer],callback);
    },

    getAllCredentials(callback){
        return db.query("SELECT * FROM credentials",callback);
    },

    addCredentials(newCredentials, callback){
        bcrypt.hash(newCredentials.password,10,function(err, hashedPassword){
            return db.query("INSERT INTO credentials VALUES(?,?,?)",
            [newCredentials.idcredentials, hashedPassword, newCredentials.idcustomer],callback);
        });
    },

    updateCredentials(idcustomer,updateCredentials, callback){
        bcrypt.hash(updateCredentials.password,10,function(err, hashedPassword){
            return db.query("UPDATE credentials SET idcredentials=?, password=? WHERE idcustomer=?",
            [updateCredentials.idcredentials, hashedPassword, idcustomer],callback);
        });
    },

    deleteCredentials(idcustomer, callback){
        return db.query("DELETE FROM credentials WHERE idcustomer=?",[idcustomer],callback);
    },
}

module.exports=credentials;
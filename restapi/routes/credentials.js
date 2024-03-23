const express = require('express');
const router = express.Router();
const credentials=require('../models/credentials_model');

router.get('/:idcustomer',function(request,response){
    credentials.getOneCredentials(request.params.idcustomer, function(err,result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result[0]);
        }
    })
});

router.get('/',function(request, response){
    credentials.getAllCredentials(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.post('/',function(request, response){
    credentials.addCredentials(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.put('/:idcustomer', function(request, response){
    credentials.updateCredentials(request.params.idcustomer, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.delete('/:idcustomer',function(request, response){
    credentials.deleteCredentials(request.params.idcustomer, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

module.exports=router;
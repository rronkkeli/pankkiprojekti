const express = require('express');
const router = express.Router();
const nostotapahtuma = require('../models/nostotapahtuma_model');

router.get('/:asiakas/:tili_numero/:nosto', function (request, response) {

    const asiakas = request.params.asiakas;
    const tili_numero = request.params.tili_numero;
    const nosto = request.params.nosto;
    nostotapahtuma.getMoneyOut(asiakas,tili_numero, nosto, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    });
});

module.exports = router;
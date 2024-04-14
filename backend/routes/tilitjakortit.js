const express = require('express');
const router = express.Router();
const tilitjakortit = require('../models/tilitjakortit_model');

router.get('/:asiakas', function (request, response) {
    const asiakas = request.params.asiakas;
    tilitjakortit.getAccountsAndCards(asiakas, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    });
});

module.exports = router;
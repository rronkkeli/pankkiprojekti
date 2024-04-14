const express = require('express');
const router = express.Router();
const tilitiedot = require('../models/tilitiedot_model');

router.get('/:asiakas', function (request, response) {
    const asiakas = request.params.asiakas;
    tilitiedot.getWithdrawakees(asiakas, function (err, dbResult) {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    });
});

module.exports = router;
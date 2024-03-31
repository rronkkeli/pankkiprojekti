const express = require('express');
const router = express.Router();
const withdrawal = require('../models/withdrawal_model');
const auth = require('../mods/auth'); // Will implemet authentication later

// Get withdrawal history for account
router.get('/:account', (req, res) => {
    // TODO: get account from authentication token instead of get data
    withdrawal.getAll(req.params.account, (err, dbResult) => {
        if (err) {
            res.json(err);
        } else {
            res.json(dbResult);
        }
    })
});

// Insert a new withdrawal for account
router.post('/', (req, res) => {
    console.log(req.body);
    withdrawal.add(req.body, (err, dbResult) => {
        if (err) {
            res.json(err);
        } else {
            res.json(dbResult);
        }
    })
});

// Update a withdrawal for account
// This should never be used in real life!
router.put('/', (req, res) => {
    withdrawal.update(req.body, (err, dbResult) => {
        if (err) {
            res.json(err);
        } else {
            res.json(dbResult);
        }
    })
});

// Delete a withdrawal from account history
// This should never be used in real life!
router.delete('/:id', (req, res) => {
    // TODO: delete withdrawal by authentication or remove feature entirely as withdrawal history should never be altered
    withdrawal.delete(req.params.id, (err, dbResult) => {
        if (err) {
            res.json(err);
        } else {
            res.json(dbResult);
        }
    })
});

module.exports = router;
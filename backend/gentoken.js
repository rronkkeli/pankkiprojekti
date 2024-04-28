const crypto = require('crypto');

console.log(
    'MY_TOKEN='+crypto.randomBytes(256).toString('base64')
);
const dotenv = require('dotenv');
dotenv.config();

// Secret server token
const secret = process.env.TOKEN_SECRET;

// Token expire time
const expires = {expiresIn: '600s'};

const jwt = require('jsonwebtoken');

// Generate access token
function generate(user) {
    return jwt.sign(user, secret, expires);
}

// Verifies the token
function verify(token) {
    jwt.verify(token, secret, (err, user) => {
        if (err) {
            return err;
        } else {
            return user;
        }
    });
}
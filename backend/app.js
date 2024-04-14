var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));


// Declare developmend modules here
const withrawalRouter = require('./routes/withdrawal');
app.use('/withdrawal', withrawalRouter);
const customerRouter = require('./routes/customer');
app.use('/customer',customerRouter);
const credentialsRouter = require('./routes/credentials');
app.use('/credentials', credentialsRouter);
const accountRouter = require('./routes/account');
app.use('/account', accountRouter);
var cardRouter = require('./routes/card');
app.use('/card', cardRouter);

const tilitjakortitRouter = require('./routes/tilitjakortit');
app.use('/tilitjakortit', tilitjakortitRouter);

const nostotapahtumaRouter = require('./routes/nostotapahtuma');
app.use('/nostotapahtuma', nostotapahtumaRouter);

const tilitiedotRouter = require('./routes/tilitiedot');
app.use('/tilitiedot', tilitiedotRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
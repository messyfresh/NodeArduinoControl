var express = require('express');
var router = express.Router();
var HOST = '172.16.0.20';
var PORT = 8888;
var dgram = require('dgram');
var client = dgram.createSocket('udp4');

/* GET home page. */
router.get('/', function(req, res) {
  res.render('index', { title: 'Express' });
});

router.post('/ledON', function (req, res) {

    var message = new Buffer('on ');

    client.send(message, 0, message.length, PORT, HOST, function (err, bytes) {
        if (err) throw err;
        console.log('Message sent to Arduino at ' + HOST + ":" + PORT);
        client.close();
    });

    res.location('/');
    res.redirect('/');
});

router.post('/ledOFF', function (req, res) {
    
    var message = new Buffer('of');

    client.send(message, 0, message.length, PORT, HOST, function (err, bytes) {
        if (err) throw err;
        console.log('Message sent to Arduino at ' + HOST + ":" + PORT);
        client.close();
    });

    res.location('/');
    res.redirect('/');
});
module.exports = router;
var PORT= 8888;
var HOST = '172.16.0.20';

var dgram = require('dgram');
var message = new Buffer('Hello Arduino, From Node');

var client = dgram.createSocket('udp4');
client.send(message, 0, message.length, PORT, HOST, function (err, bytes) {
    if (err) throw err;
    console.log('Message sent to Arduino at ' + HOST + ":" + PORT);
    client.close();
});


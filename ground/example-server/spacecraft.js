/*
 Spacecraft.js simulates a small spacecraft generating telemetry.
*/

const SerialPort = require('serialport');
const Readline = SerialPort.parsers.Readline;
var parser = new Readline();
var serialport = new SerialPort("/dev/ttyACM0", {
    baudRate: 115200
});

function Spacecraft() {
    this.state = {
        "prop.temp": 0.0,
        "prop.hum": 0.0,
        "prop.pressure": 0.0,
        "prop.magx": 0.0,
        "prop.magy": 0.0,
        "prop.magz": 0.0,
        "prop.accx": 0.0,
        "prop.accy": 0.0,
        "prop.accz": 0.0,
    };

    this.history = {};
    this.listeners = [];
    Object.keys(this.state).forEach(function(k) {
        this.history[k] = [];
    }, this);

    serialport.pipe(parser);
    parser.on('data', function(data) {
        this.updateState(data);
        this.generateTelemetry();
    }.bind(this));
};

Spacecraft.prototype.updateState = function(data) {
    console.log(data);
    parsedData = ReadSerial(data);
    if (parsedData) {
        this.state = {
            "prop.temp": parsedData['temperature'],
            "prop.hum": parsedData['hum'],
            "prop.pressure": parsedData['pressure'],
            "prop.accx": parsedData['acc_x'],
            "prop.accy": parsedData['acc_y'],
            "prop.accz": parsedData['acc_z'],
            "prop.magx": parsedData['mag_x'],
            "prop.magy": parsedData['mag_y'],
            "prop.magz": parsedData['mag_z']
        };
    }
};

/**
 * Takes a measurement of spacecraft state, stores in history, and notifies 
 * listeners.
 */
Spacecraft.prototype.generateTelemetry = function() {
    console.log(this.state);
    var timestamp = Date.now(),
        sent = 0;
    Object.keys(this.state).forEach(function(id) {
        var state = {
            timestamp: timestamp,
            value: this.state[id],
            id: id
        };
        this.notify(state);
        this.history[id].push(state);
    }, this);
};

Spacecraft.prototype.notify = function(point) {
    this.listeners.forEach(function(l) {
        l(point);
    });
};

Spacecraft.prototype.listen = function(listener) {
    this.listeners.push(listener);
    return function() {
        this.listeners = this.listeners.filter(function(l) {
            return l !== listener;
        });
    }.bind(this);
};


function ReadSerial(data) {
    return parseSerial(data)
};

function hexToBytes(hex) {
    for (var bytes = [], c = 0; c < hex.length; c += 2)
        bytes.push(parseInt(hex.substr(c, 2), 16));
    return bytes;
};

function bytesToFloat(bytes) {
    var buf = new ArrayBuffer(4);
    var view = new DataView(buf);
    bytes.forEach(function(b, i) {
        view.setUint8(i, b);
    });
    return view.getFloat32(0);
};

function parseSerial(data) {
    console.log(data);
    if (data.startsWith("16")) {
        if (data.slice(2, -1).startsWith('01')) { // TELEM
            var acc_x = bytesToFloat(hexToBytes(data.slice(10, 12) + data.slice(8, 10) + data.slice(6, 8) + data.slice(4, 6)));
            var acc_y = bytesToFloat(hexToBytes(data.slice(18, 20) + data.slice(16, 18) + data.slice(14, 16) + data.slice(12, 14)));
            var acc_z = bytesToFloat(hexToBytes(data.slice(26, 28) + data.slice(24, 26) + data.slice(22, 24) + data.slice(20, 22)));
            var hum = bytesToFloat(hexToBytes(data.slice(34, 36) + data.slice(32, 34) + data.slice(30, 32) + data.slice(28, 30)));
            var mag_x = bytesToFloat(hexToBytes(data.slice(42, 44) + data.slice(40, 42) + data.slice(38, 40) + data.slice(36, 38)));
            var mag_y = bytesToFloat(hexToBytes(data.slice(50, 52) + data.slice(48, 50) + data.slice(46, 48) + data.slice(44, 46)));
            var mag_z = bytesToFloat(hexToBytes(data.slice(58, 60) + data.slice(56, 58) + data.slice(54, 56) + data.slice(52, 54)));
            var pressure = bytesToFloat(hexToBytes(data.slice(66, 68) + data.slice(64, 66) + data.slice(62, 64) + data.slice(60, 62)));
            var temperature = bytesToFloat(hexToBytes(data.slice(74, 76) + data.slice(72, 74) + data.slice(70, 72) + data.slice(68, 70)));
            return {
                "acc_x": acc_x,
                "acc_y": acc_y,
                "acc_z": acc_z,
                "hum": hum,
                "mag_x": mag_x,
                "mag_y": mag_y,
                "mag_z": mag_z,
                "pressure": pressure,
                "temperature": temperature
            }
        }

    }
};


module.exports = function() {
    return new Spacecraft()
};
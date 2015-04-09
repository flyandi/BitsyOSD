/**
   ___  _ __           ____  _______ 
  / _ )(_) /____ __ __/ __ \/ __/ _ \
 / _  / / __(_-</ // / /_/ /\ \/ // /
/____/_/\__/___/\_, /\____/___/____/ 
               /___/                 

Font Upload Tool

**/

/**
  * Configuration
  */

var // the font file to be uploaded
    FONT_FILE = "bitsyosd-font.mcm",
    // set the serial speed (baud)
    SERIAL_BAUD = 115200,
    // set the serial device, leave false to choose
    SERIAL_DEVICE = null; 


/**
  * Objects
  */

var SerialPort = require("serialport").SerialPort,
    SerialList = require("serialport"),
    File = require('read-file'),
    Prompt = require('readline-sync'),
    ProgressBar = require('progress'),
    Runtime = {
      uploading: false
    };

/** 
  * (run) 
  */

var run = function() {
    try {
    if(SERIAL_DEVICE == null) {
      console.log('No valid COM Port selected.');
    } else {
      // initialize port
      var serialPort = new SerialPort(SERIAL_DEVICE, {baudrate: SERIAL_BAUD});
      // open serial port
      serialPort.on("open", function () {
        // new bar
        var d = (File.readFileSync(FONT_FILE)).split("\n"),
            bar = new ProgressBar(':bar', { total: d.length });
        // serial port
        serialPort.on('data', function(buffer) {
          // prepare data
          var data = (''+buffer).trim();
          
          // wait for start marker
          switch(true) {
            case data == 'R' && !Runtime.uploading:
              // block 
              Runtime.uploading = true;
              // load font and upload
              console.log('Reading font...');
              // make sure it's a valid file
              console.log(d[0] == 'MAX7456');
              if(d[0] == 'MAX7456' || true) {
                // cycle in pairs of 8
                setTimeout(function() {
                  console.log("Uploading font...");
                  var x = 0;
                  for(var i = 1; i < d.length; i++) {
                    var m = (d[i]).trim();
                    serialPort.write(m + "\r");
                  }
                }, 100);

              } else {
                console.log('Invalid font. Not recgonized.');
                process.exit();
              }
              break;

            case data.toLowerCase() == 'd':
              console.log('Font was successfully uploaded. All done.');
              // terminate application
              process.exit();
              break;

            case data == '+':
              if(!bar.complete) bar.tick();
              break;
          }
      
        });
      });
    }
  } catch(e) {
    console.log('\nError: ' + e + '\n');
  }
}

//

if (!SERIAL_DEVICE) {
  // display ports
  SerialList.list(function (err, ports) {
    // show ports
    ports.forEach(function(port, index) {
      console.log(index + ' - ' + port.comName);
    });

    // create question
    var answer = parseInt(Prompt.question('\nEnter COM Port: '));

    // set port
    SERIAL_DEVICE = answer >= 0 && answer < ports.length ? ports[answer].comName : null;

    // run serial
    run();
  });
} else {
  // run serial
  run();
}
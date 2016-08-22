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
    SERIAL_BAUD = 19200,
    // set the serial device, leave false to choose
    SERIAL_DEVICE = null; 


/**
  * Objects
  */

var SerialPort = require("serialport"),
    fs = require('fs'),
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

        // load
        fs.readFile(FONT_FILE, "utf-8", function(err, fileData) {

          // error handling
          if(err) throw err;

          // transform data
          var d = fileData.split("\n");

          // initialize bar
          var bar = new ProgressBar(':bar :current :percent', { total: d.length }),

              pos = 1; // first position

          var next = function() {
            serialPort.write(d[pos] + "\r");
            pos++;
          } 


          // serial port
          serialPort.on('data', function(buffer) {
            // prepare data
            var data = (''+buffer).trim().substr(0, 1);

            // wait for start marker
            switch(true) {
              case data.toLowerCase() == 'r':
                console.log("Restarting font upload");
                pos = 1;
                next();
                break;
             
              case data.toLowerCase() == 'd':
                console.log('Font was successfully uploaded. All done.');
                // terminate application
                process.exit();
                break;

              case data == '+':
                if(!bar.complete) bar.tick();
                next();
                break;
            }
        
          });

          // font upload starter
          setTimeout(function() {
            next();
          }, 500);
        
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
  SerialPort.list(function (err, ports) {
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
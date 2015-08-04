/**
   ___  _ __           ____  _______ 
  / _ )(_) /____ __ __/ __ \/ __/ _ \
 / _  / / __(_-</ // / /_/ /\ \/ // /
/____/_/\__/___/\_, /\____/___/____/ 
               /___/                 

Helpers                                         

**/

/**
  * (Helpers)
  */

void unplugSlaves() {
    //Unplug list of SPI
    digitalWrite(MAX7456_SELECT, HIGH); // unplug OSD
}


/**
 * (ReadVoltage)
 */

float ReadVoltage(int pin, int divider) {

  static uint16_t i = 0;
  static uint32_t raw[8];
  uint16_t voltageRaw = 0;

  // read raw voltage from pin
  raw[(i++)%8] = analogRead(pin); 

  // process
  for (uint16_t i=0;i<8;i++)
  voltageRaw += raw[i];

  // return voltage
  float voltage = float(voltageRaw) * divider / 1023; 
  
  return voltage;    
}

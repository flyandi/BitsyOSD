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


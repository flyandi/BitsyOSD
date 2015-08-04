/**
   ___  _ __           ____  _______ 
  / _ )(_) /____ __ __/ __ \/ __/ _ \
 / _  / / __(_-</ // / /_/ /\ \/ // /
/____/_/\__/___/\_, /\____/___/____/ 
               /___/                 

GPS Simulated Parser

Great for development!                                         

**/

#ifdef GPS_PARSER_SIM
#define GPS_PARSER

#include "gps.h"

long tsimtick = millis();
long tsimsec = millis();


static struct GPS_DATA GPSValues;

/** 
  * (gps_process) Processes the GPS Data
  */

boolean gps_process(void) {
  
  if(GPSValues.Satellites != 9) { 
    GPSValues.Satellites = 9;
    GPSValues.Status = GPS_STATUS_FIX3D;
    GPSValues.Latitude = 33.121076; // Carlsbad, CA
    GPSValues.Longitude = -117.327671; 
    GPSValues.Altitude = 100; 
    GPSValues.Heading = 180;
    GPSValues.Groundspeed = 0;
    GPSValues.Climbrate = 5.5;
  }
  
  // check home .. simulating some coordinates here
  if(runtime.gpshashome) {
     GPSValues.Latitude =  33.121656;
     GPSValues.Longitude = -117.328118;
  
    // simulate altitude
    if(tsimsec + 5000 < millis()) {
       GPSValues.Altitude = GPSValues.Altitude == 100 ? 200 : 100; 
       GPSValues.Groundspeed = GPSValues.Groundspeed == 0 ? 22.5 : 0;
       tsimsec = millis();
    }
    
    // simulate heading
    if(tsimtick + 1000 < millis()) {
       GPSValues.Heading = GPSValues.Heading + 10;
       if(GPSValues.Heading >= 360) GPSValues.Heading = 0;     
       tsimtick = millis(); 
    }
  }

  return true;	// always got data
}

/**
  * (gps_values) Returns the GPS Values
  */

GPS_DATA gps_values() {

  return GPSValues;
 
 }



#endif


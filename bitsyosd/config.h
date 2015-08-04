/**
   ___  _ __           ____  _______ 
  / _ )(_) /____ __ __/ __ \/ __/ _ \
 / _  / / __(_-</ // / /_/ /\ \/ // /
/____/_/\__/___/\_, /\____/___/____/ 
               /___/                 

This is your configuration file! It defines some basic parameters that you can
tweak to your likening.                                                    

**/

#ifndef _CONF_
#define _CONF_

#include "const.h";


/** 
  * (Video Mode)
  * 
  * 0 = PAL
  * 1 = NTSC
  */
  
#define VIDEO_MODE 1


/**
  * (Units) 
  * 
  * Pick and choose the units you like for the different parameters
  */


#define UNIT_SPEED UNIT_SPEED_MPH
#define UNIT_ALTITUDE UNIT_LENGTH_FT
#define UNIT_LENGTH UNIT_LENGTH_FT
#define UNIT_DISTANCE UNIT_LENGTH_FT
#define UNIT_DISTANCE_LARGE UNIT_LENGTH_MI


/**
  * (Showlabels)
  *
  * If enabled, it will show labels on various location. Can clutter the interface.
  *
  * true = Enabled
  * false = Disabled
  *
  */
  
#define SHOW_LABELS true


/**
  * (GPS Parser)
  * 
  * BitsyOSD can handle different parser formats, you need to choose one here
  *
  * Uncomment one of the options below. If you want to test the OSD without GPS, use the SIM parser.
  */

#define GPS_PARSER_NEMA
//#define GPS_PARSER_DJI
//#define GPS_PARSER_UBLOX
//#define GPS_PARSER_SIM


/** 
  * (GPS Serial Speed)
  *
  * The serial baud rate of the attached GPS
  *
  * Some default rates
  * UBLOX 6M     9600
  * DJI GPS      115200
  *
  */

// Ublox
#define GPS_SPEED 9600 

// DJI
//#define GPS_SPEED 115200


/**
* (GPS Required Satellites)
* 
* The required satellites before anything starts. You want to have this at
* something like >= 5 to get decent GPS information.
*/

#define GPS_REQUIRED_SAT 5


/**
  * (GPS Heading Interpolation)
  *
  * Value to interpolate the heading so it doesn't jump around like crazy
  */
  
#define GPS_HEADING_INTERPOLATE 2


/** 
  * (GPS Altitude Type)
  *
  * 0 = AGL (Above Ground Level)
  * 1 = ASL (Above Sea Level)
  */
  
#define GPS_ALTITUDE_TYPE 0


/** 
  * (GPS Accuracy)
  * 
  * Adjust this value to get better values. If you are in a region with not so good GPS
  * reception, please leave it at Standard.
  *
  * 1 = Standard
  * 2 = Better
  */
  
#define GPS_ACCURACY 1


/**
  * (GPS Precision)
  *
  * The GPS Coordinates precision - only for display
  */
  
#define GPS_PRECISION 5


/**
  * (GPS Coodinates)
  *
  * Enables the display of the current GPS Coordinates if uncommented
  * 
  */

#define GPS_COORDINATES_SHOW


/**
  * (Home Bearing)
  *
  * Defines the type of home bearing. See below:
  *
  * 0 = (AHB) Absolute Home Bearing - the arrow always points to home, regardless of the current active heading
  * 1 = (RHB) Relative Home Bearing - the arrow is showing the relative home bearing based on the current heading.
  *
  * It's absolutly a preference choice here, however RBH makes the most sense.
  * 
  */
  
#define HOME_BEARING 1


/**
  * (Voltage) 
  * 
  * Enables to display the battery voltage. Only supported on the Micro MinimOSD Hardware.
  * Don't forget to set the proper Voltage divider.
  *
  * 0 = Off (Default)
  * 1 = Bat1  (Only shows Battery 1)
  * 2 = Bat2  (Only shows Battery 2)
  * 3 = All   (Shows both Batteries)
  */

//#define SHOW_VOLTAGE 0

/**
  * (Voltage Divider) 
  * 
  * If you enable the voltage display, you need to set the voltage divider to see proper
  * Battery voltages on your screen. 
  *
  * 2s = 
  * 1 = Bat1  (Only shows Battery 1)
  * 2 = Bat2  (Only shows Battery 2)
  * 3 = All   (Shows both Batteries)
  */

//#define VOLTAGE_DIVIDER_BATTERY1 0
//#define VOLTAGE_DIVIDER_BATTERY2 0


/** 
  * (RSSI)
  *
  * Displayes the current RSSI strength. Only supported on the Micro MinimOSD Hardware.
  *
  * 0 = Off (Default)
  * 1 = On  
  */

//#define SHOW_RSSI 0


#endif /* _CONF_ */
  


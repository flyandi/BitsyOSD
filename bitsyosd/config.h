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
  *
  */

//#define GPS_PARSER_NEMA
//#define GPS_PARSER_DJI
//#define GPS_PARSER_UBLOX
#define GPS_PARSER_SIM


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
  * NOTE: You need to define the Voltage Divider and Battery type for each type you want to display.
  *       Otherwise it won't compile.
  *
  * 0 = Off (Default)
  * 1 = Bat1  (Only shows Battery 1)
  * 2 = Bat2  (Only shows Battery 2)
  * 3 = All   (Shows both Batteries)
  *
  */

#define SHOW_VOLTAGE 1


/**
  * (Configuration for LiPo)
  *
  * Specify the min and max voltage of a cell
  *
  */
  
#define CELL_MAX_VOLTAGE 4.2
#define CELL_MIN_VOLTAGE 3.6
#define CELL_ALERT_VOLTAGE 3.75    // Used for Low Battery warning


/**
  * Additional you can specify to show each battery as voltage or percentage
  *
  * Note: Nothing is displayed if no battery voltage is detected.
  *
  * 0 = Default (Voltage)
  * 1 = Percentage
  * 2 = Toggle (every 5s) ** NOT IMPLEMENTED YET **
  */

#define DISPLAY_MODE_BATTERY1 0
#define DISPLAY_MODE_BATTERY2 0


/**
  * (Voltage Divider) 
  * 
  * If you enable the voltage display, you need to set the voltage divider to see proper
  * Battery voltages on your screen. 
  *
  */

#define VOLTAGE_DIVIDER_BATTERY1 10
#define VOLTAGE_DIVIDER_BATTERY2 10


/**
  * (Battery Types)
  * 
  * For accurate display, please specify the type of Battery used on each port.
  *
  * 1s = 0  - Probably never been used
  * 2s = 1
  * 3s = 2
  * 4s = 3  - Maximum supported by the Hardware
  */

#define TYPE_BATTERY1 2
#define TYPE_BATTERY2 2



/**
  * (Battery Alarm) 
  *
  * Shows an alert if the voltage drops below a certain cell voltage. 
  *
  * Don't forget to set the cell voltage. This can be different from the minimum cell voltage.
  *
  * 0 = Off (Default)
  * 1 = On
  *
  */

#define SHOW_BATTERY_ALERT 1


/** 
  * (RSSI) Experimental / Not field tested
  *
  * Displayes the current RSSI strength. Only supported on the Micro MinimOSD Hardware.
  *
  * 0 = Off (Default)
  * 1 = On  
  */

//#define SHOW_RSSI 0



#endif /* _CONF_ */

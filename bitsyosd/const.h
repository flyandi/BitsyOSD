/**
   ___  _ __           ____  _______ 
  / _ )(_) /____ __ __/ __ \/ __/ _ \
 / _  / / __(_-</ // / /_/ /\ \/ // /
/____/_/\__/___/\_, /\____/___/____/ 
               /___/             
 * 
 * This file defines some of the constants used throughout the
 * OSD. If you don't like the layout of the OSD, you may can 
 * tweak some of the values here.   
 * 
 * NOTE: ANY MODIFICATION TO THIS FILE MIGHT BRICK YOUR OSD.
 *       MAKE SURE YOU KNOW WHAT YOU DOING!
 * 
 **/

#ifndef _CONST_
#define _CONST_

/**
 * (Conversions)
 */

#define UNIT_SPEED_MS 1.0
#define UNIT_SPEED_KMH 3.6
#define UNIT_SPEED_MPH 2.23
#define UNIT_SPEED_KN 1.94

#define UNIT_LENGTH_M 1.0
#define UNIT_LENGTH_KM 0.001
#define UNIT_LENGTH_FT 3.28084
#define UNIT_LENGTH_MI 0.000621371
#define UNIT_LENGTH_NM 0.000539957


/**
 * (Fonts) 
 *
 * How cool! There are four fonts within the character set.
 *
 * Large = The large standard font, includes A-Z and 0-9
 * Small = The same standard font, just smaller
 * Segment Large = A segment font, only includes 0-9
 * Segment Small = A smaller version of the segment font
 *
 */

#define FONT_LARGE           0x01
#define FONT_SMALL           0x25
#define FONT_SEGMENTLARGE    0xf0
#define FONT_SEGMENTSMALL    0xe0


/**
 * (Symbols) 
 *
 * This defines the different symbols from the character set
 */

#define NO_SYMBOL            0
#define SYMBOL_BATTERY_100   0x70
#define SYMBOL_BATTERY_60    0x71
#define SYMBOL_BATTERY_30    0x72
#define SYMBOL_BATTERY_0     0x73
#define SYMBOL_GPS           0x80
#define SYMBOL_PLANE         0x82
#define SYMBOL_HOME          0x87
#define SYMBOL_HOURGLASS     0x8c
#define SYMBOL_TIMER         0x8d
#define SYMBOL_SPEED         0x8a
#define SYMBOL_ALT           0x88
#define SYMBOL_FEET          0x96
#define SYMBOL_MPH           0xa6
#define SYMBOL_WARN0         0x77
#define SYMBOL_WARN1         0x78
#define SYMBOL_HEARTBEAT     0x9a
#define SYMBOL_DEGREE        0x4d
#define SYMBOL_NOCLIMB       0x9b
#define SYMBOL_CLIMBUP       0x9e
#define SYMBOL_CLIMBDOWN     0x9f
#define SYMBOL_FLAG          0x81
#define SYMBOL_TIMEON        0x7f
#define SYMBOL_TIMEFLY       0x7e
#define SYMBOL_LAT           0x6e
#define SYMBOL_LON           0x6f
#define SYMBOL_RSSI          0x86
#define SYMBOL_PERCSMALL     0x92
#define SYMBOL_PERCLARGE     0x4c

/**
 * (Layout) 
 *
 * This defines the positions of the different values displayed on the OSD
 */

#define LAYOUT_SPEED_X        3
#define LAYOUT_SPEED_Y        6

#define LAYOUT_ALT_X          23 
#define LAYOUT_ALT_Y          6

#define LAYOUT_CLIMB_X        21
#define LAYOUT_CLIMB_Y        6

#define LAYOUT_GPS_X          26
#define LAYOUT_GPS_Y          1

#define LAYOUT_WARN_X         14
#define LAYOUT_WARN_Y         1

#define LAYOUT_LOWVOLT_X      12
#define LAYOUT_LOWVOLT_Y      3

#define LAYOUT_HEADING_X      13
#define LAYOUT_HEADING_Y      1

#define LAYOUT_HOME_X         22
#define LAYOUT_HOME_Y         1

#define LAYOUT_HOMEBEARING_X  14
#define LAYOUT_HOMEBEARING_Y  2

#define LAYOUT_OSDTIME_X      2
#define LAYOUT_OSDTIME_Y      11

#define LAYOUT_FLYTIME_X      22
#define LAYOUT_FLYTIME_Y      11

#define LAYOUT_HOMEDISTANCE_X 22
#define LAYOUT_HOMEDISTANCE_Y 9

#define LAYOUT_DISTANCE_X     22
#define LAYOUT_DISTANCE_Y     10

#define LAYOUT_GPSCOORD_X     2
#define LAYOUT_GPSCOORD_Y     9

#define LAYOUT_PROGRESS_X     12
#define LAYOUT_PROGRESS_Y     5

#define LAYOUT_BATTERY1_X     2
#define LAYOUT_BATTERY1_Y     1

#define LAYOUT_BATTERY2_X     2
#define LAYOUT_BATTERY2_Y     2

/**
 * (Control)
 * 
 * Control Characters
 */

#define CHAR_CLEAR           0xee
#define CHAR_BLACK           0xfe
#define CHAR_WHITE           0xff


/**
 * (Definitions) 
 */
 
#define BOOTTIME            5000


/** 
 * (LED)
 */

#define LED_HEARTBEAT 1200
#define LED_PIN 13

/** 
 * (Voltage, Current and RSSI)
 */

#define VOLTAGE_PIN_BATTERY1 A2
#define VOLTAGE_PIN_BATTERY2 A0
#define CURRENT_PIN A1
#define RSSI_PIN A3 

/** 
 * (Development)
 */

//#define SIMULATE  // Only enable if you really code - because this will knock out all real data

/** 
 * (Runtime Values) 
 */

struct OSD_RUNTIME_VALUES {

  // OSD 
  boolean osdredraw;
  unsigned long tosdtime;

  // GPS
  boolean gpswarn;
  boolean gpshashome;
  float gpsheading;
  float gpsasl;
  float gpshomelat;
  float gpshomelon;
  long gpshomebearing;
  long gpshomedirection;
  long gpshomedistance;
  uint8_t gpsclimb;
  float gpsaltprev;
  uint8_t gpsaltcount;
  boolean gpsacquired;
  long gpstimeout;
  
  // LED
  bool ledstatus;
  long ledtimeout;

  // Other
  long distance;
  unsigned long tdistance;

  // Fly Timer
  long flytime;
  long flytimelast;

  // RSSI
  float rssi;

  // Voltage
  float voltage1;
  float voltage2;
  
  // other timeouts
  long tvalues;
};


#endif /* _CONST_ */




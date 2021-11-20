/**
   ___  _ __           ____  _______ 
  / _ )(_) /____ __ __/ __ \/ __/ _ \
 / _  / / __(_-</ // / /_/ /\ \/ // /
/____/_/\__/___/\_, /\____/___/____/ 
               /___/             
 *
 * This file defines the defaults if the configuration doesn't
 * reflect it. It's better to define it in config.h than editing
 * this file.
 *
 * NOTE: ANY MODIFICATION TO THIS FILE MIGHT BRICK YOUR OSD.
 *       MAKE SURE YOU KNOW WHAT YOU DOING!
 *
 **/

#ifndef _DEFAULTS_
#define _DEFAULTS_

#include "const.h";
#include "config.h";

/**
 * (GPS)
 */

// Common GPS defaults
#define GPS_AGL_NEGATIVE    5         // 5m safety distance before negative values are displayed
#define GPS_CLIMB_VALUE     8         // Minimum climb up down value - anything between +/- of this value will be considered no movement
#define GPS_MEASURE_PERIOD  95        // Period for meassuring distance
#define GPS_MEASURE_FLYTIME 3         // Minimum value for meassuring flight
#define GPS_TIMEOUT         4000      // timeout for lost GPS

// Home locks
#ifndef GPS_HOME_WAIT
#ifdef GPS_PARSER_NEMA
#define GPS_HOME_WAIT     10        // Wait count for Home, 5 is pretty large for NEMA since it's very unstable but good enough.
#else
#define GPS_HOME_WAIT     50      // UBlox, DJI - both need a bit more time for locking in home
#endif
#endif

#ifndef GPS_HOME_SENSITIVITY
#ifdef GPS_PARSER_NEMA
#define GPS_HOME_SENSITIVITY 3       // NEMA is rounded, so it can jump crazy 
#else
#define GPS_HOME_SENSITIVITY 0.5     // UBlox, DJI - using floats, less jumpy when accurate
#endif
#endif


#endif /* _DEFAULTS_ */

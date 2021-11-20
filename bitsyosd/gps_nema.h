/**
   ___  _ __           ____  _______ 
  / _ )(_) /____ __ __/ __ \/ __/ _ \
 / _  / / __(_-</ // / /_/ /\ \/ // /
/____/_/\__/___/\_, /\____/___/____/ 
               /___/                 

GPS NEMA Parser                                      

**/

#ifndef GPS_P_H
#define GPS_P_H

// Runtime variables
static int32_t NEMA_static_lat;
static int32_t NEMA_static_lon;
static int32_t NEMA_bearing_lat;
static int32_t NEMA_bearing_lon;

static float NEMA_lon_scaleup;
static float NEMA_lon_scaledown;

// Moving Variables
static uint32_t NEMA_lastframe_time = 0;


#endif /* GPS_PARSER */


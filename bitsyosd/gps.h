/**
   ___  _ __           ____  _______ 
  / _ )(_) /____ __ __/ __ \/ __/ _ \
 / _  / / __(_-</ // / /_/ /\ \/ // /
/____/_/\__/___/\_, /\____/___/____/ 
               /___/                 

Generic GPS Information                                          

**/

#ifndef GPS
#define GPS

/**
  * (Constants)
  */

#define GPS_STATUS_NOGPS	0
#define GPS_STATUS_NOFIX	1
#define GPS_STATUS_FIX2D	2
#define GPS_STATUS_FIX3D	3


/** 
  * (struct) GPS_DATA
  * Primary structure for GPS data
  */

typedef struct GPS_DATA {
    uint8_t	Status;
    uint8_t	Satellites;
    float	Latitude;
    float	Longitude;
    float	Altitude;
    float	Heading;
    float	Groundspeed;
    float	Climbrate;
    uint32_t    Time;
};

#endif /* GPS */



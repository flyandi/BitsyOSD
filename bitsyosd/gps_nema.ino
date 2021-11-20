/**
   ___  _ __           ____  _______ 
  / _ )(_) /____ __ __/ __ \/ __/ _ \
 / _  / / __(_-</ // / /_/ /\ \/ // /
/____/_/\__/___/\_, /\____/___/____/ 
               /___/                 

GPS NEMA Parser                                      

**/


#ifdef GPS_PARSER_NEMA
#define GPS_PARSER

#include "gps.h"
#include "gps_nema.h"

static struct GPS_DATA GPSValues;


/** 
  * (gps_process) Processes the GPS Data
  */
  
boolean gps_process(void) {
  // read serial
  
  while (Serial.available()) {
    // process frame
    if(NEMA_parse(Serial.read())) { 

      // calculate
      NEMA_longitude_scaling(NEMA_static_lon);
      
      // calculate extra values
      GPSValues.Heading = NEMA_bearing(NEMA_bearing_lat, NEMA_bearing_lon, NEMA_static_lat, NEMA_static_lon);

      // update 
      NEMA_bearing_lat = NEMA_static_lat;
      NEMA_bearing_lon = NEMA_static_lon;

      // Climb
      GPSValues.Climbrate = 0;

      // return 
      return true;
    }
  }

  return false;
}


/**
  * (gps_values) Returns the GPS Values
  */
  
GPS_DATA gps_values() {
  return GPSValues;
}


/** 
  * (NEMA_longitude_scaling)
  */
void NEMA_longitude_scaling(int32_t lat) {
  float rads  = (abs((float)lat) / 10000000.0) * 0.0174532925;
  NEMA_lon_scaledown  = cos(rads);
  NEMA_lon_scaleup  = 1.0f / cos(rads);
}


/**
  * (NEMA_bearing) calculates bearing between two points 
  */

int32_t NEMA_bearing(int32_t lat1, int32_t lon1, int32_t lat2, int32_t lon2) {

  float off_x = (float)lon2 - lon1;
  float off_y = ((float)(lat2 - lat1)) * NEMA_lon_scaleup;
  float bearing = 9000.0f + atan2(-off_y, off_x) * 5729.57795f;      //Convert the output redians to 100xdeg

  if (bearing < 0) bearing += 36000;
  
  return bearing/100;
}


/* (NEMA_ctd - Coordinates to degrees) */
#define DIGIT_TO_VAL(_x)  (_x - '0')
uint32_t NEMA_ctd(char* s) {
  char *p, *q;
  uint8_t deg = 0, min = 0;
  unsigned int frac_min = 0;

  // scan for decimal point or end of field
  for (p = s; isdigit(*p); p++)
    ;
  q = s;

  // convert degrees
  while ((p - q) > 2) {
    if (deg)
      deg *= 10;
    deg += DIGIT_TO_VAL(*q++);
  }
  // convert minutes
  while (p > q) {
    if (min)
      min *= 10;
    min += DIGIT_TO_VAL(*q++);
  }
  // convert fractional minutes
  // expect up to four digits, result is in
  // ten-thousandths of a minute
  if (*p == '.') {
    q = p + 1;
    for (int i = 0; i < 4; i++) {
      frac_min *= 10;
      if (isdigit(*q))
        frac_min += *q++ - '0';
    }
  }
  return (deg * 10000000UL + ((min * 1000000UL + frac_min * 100UL) / 6));
}

/**
  * (NEMA_parse) Processes a new NEMA Frame 
  */

#define NO_FRAME    0
#define GPGGA_FRAME 1
#define GPGSA_FRAME 2
#define GPRMC_FRAME 3

bool NEMA_parse(char c) {

  /**
    * Variables
    */

  uint8_t frameOK = 0;
  static uint8_t param = 0, offset = 0, parity = 0;
  static char string[15];
  static uint8_t checksum_param, gps_frame = NO_FRAME;

  /** 
    * Switch by Frame Type
    */

  switch (c) {

    case '$': 
      param = 0; 
      offset = 0; 
      parity = 0; 
      break;

    case ',':
    case '*':  

      // build offset and frame identification
      string[offset] = 0;
      if (param == 0) { 
        gps_frame = NO_FRAME;  
        if (string[0] == 'G' && string[1] == 'P' && string[2] == 'G' && string[3] == 'G' && string[4] == 'A') gps_frame = GPGGA_FRAME;
        if (string[0] == 'G' && string[1] == 'P' && string[2] == 'G' && string[3] == 'S' && string[4] == 'A') gps_frame = GPGSA_FRAME;
        if (string[0] == 'G' && string[1] == 'P' && string[2] == 'R' && string[3] == 'M' && string[4] == 'C') gps_frame = GPRMC_FRAME;
      }

      /**
        * Switch by frame type
        */

      switch (gps_frame) {

        /**
          * GPGGA_FRAME
          */
        case GPGGA_FRAME: 

          switch (param) {

            // (Time) up to .000s precision
            case 1: 
              GPSValues.Time = (atof(string)*1000);
              break;

            // (Latitude)
            case 2: 
              NEMA_static_lat = NEMA_ctd(string);
              GPSValues.Latitude = (float) NEMA_static_lat / 10000000.0;
              break;

            // (Latitude / S)
            case 3: 
              if (string[0] == 'S') {
                NEMA_static_lat = -NEMA_static_lat;
                GPSValues.Latitude = -GPSValues.Latitude;
              }
              break;

            // (Longitude)
            case 4: 
              NEMA_static_lon = NEMA_ctd(string);
              GPSValues.Longitude = (float) NEMA_static_lon / 10000000.0;
              break;

            // (Longitude / W)
            case 5: 
              if (string[0] == 'W') {
                  NEMA_static_lon = -NEMA_static_lon;
                  GPSValues.Longitude = -GPSValues.Longitude;
              }
              break;

            // (Status / 2DFix)
            case 6: 
              GPSValues.Status = (string[0]  > '0') ? GPS_STATUS_FIX2D : GPS_STATUS_NOFIX;
              break;

            // (Satellites)
            case 7: 
              GPSValues.Satellites = atoi(string);
              break;

            // (Altitude)
            case 9: 
              GPSValues.Altitude = atoi(string);
              break;
          }

          break; 


        /**
          * GPGSA_FRAME
          */

        case GPGSA_FRAME:
          
          switch (param) {

            // (Status / 3DFix)
            case 2: 
              if(string[0] == '3') GPSValues.Status = GPS_STATUS_FIX3D;
              break;
          }
          break;


        /**
          * GPGSA_FRAME
          */

        case GPRMC_FRAME:

          switch(param) {
          
            // (Groundspeed)
            case 7:
              // raw value = atof(string)
              GPSValues.Groundspeed = (atof(string) * 0.5144444); // m/s
              break;

            // (Groundcourse)
            case 8:
              //GPSValues.Heading = (atof(string)*10);
              break;
          }          
          break;                   
      }

      // finalize frame
      param++; 
      offset = 0;
      if (c == '*') {
        checksum_param=1;
      } else {
        parity ^= c;
      }
      break;

    case '\r':
    case '\n':  
        if (checksum_param) { //parity checksum
          uint8_t checksum = 16 * ((string[0]>='A') ? string[0] - 'A'+10: string[0] - '0') + ((string[1]>='A') ? string[1] - 'A'+10: string[1]-'0');
          if (checksum == parity) frameOK = 1;
        }
        checksum_param=0;
        break;

      default:
        if (offset < 15) string[offset++] = c;
        if (!checksum_param) parity ^= c;
        break;
  }

  // verify frame
  if (frameOK) {
    NEMA_lastframe_time = millis();
  }

  return frameOK && (gps_frame == GPGGA_FRAME);
}

#endif /* GPS_PARSER */


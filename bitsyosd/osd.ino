/**
   ___  _ __           ____  _______ 
  / _ )(_) /____ __ __/ __ \/ __/ _ \
 / _  / / __(_-</ // / /_/ /\ \/ // /
/____/_/\__/___/\_, /\____/___/____/ 
               /___/                 

OSD Functions                                

**/

/**
  * (MessageAlert) Clear/adds an warn message on the screen
  */
  
void MessageAlert(boolean show, char* msg) {
  CustomMessageAlert(show, msg, LAYOUT_WARN_X, LAYOUT_WARN_Y, true);
}

void CustomMessageAlert(boolean show, char* msg, byte x, byte y, bool symbol) {
  
  // draw symbol
  osd.setPanel(vma(x, -1), y);
  osd.openPanel();
  if(show && symbol) {
    osd.write(SYMBOL_WARN0);
    osd.write(SYMBOL_WARN1);
  } else {
    osd.write(CHAR_CLEAR);
    osd.write(CHAR_CLEAR);
  }
  osd.closePanel();
  // draw text
  if(show) {
    osd.setPanel(vma(x, -1) - (sizeof msg/2)-1, y+ (symbol ? 1 : 0));
  } else {
    osd.setPanel(vma(x, -1) - 5, y+ (symbol ? 1 : 0));
  }
  osd.openPanel();
  if(show) {
    osd.writeupper(msg);
  } else {
    for(byte i=0;i<10;i++) {
     osd.write(CHAR_CLEAR);
    }
  }
  osd.closePanel();
}


/**
  * (DrawStatus) Draws or clears a symbol
  */

void DrawStatus(byte x, byte y, boolean b, byte symbol) {
  osd.openSingle(x, y);
  osd.write(b?symbol:CHAR_CLEAR); 
}


/**
  * (DrawThreeDigitValue) Draws a three digit value
  */

void DrawThreeDigitValue(byte x, byte y, int v, byte symbol) {
  // verify
  if(v < 0 || v > 999) return;

  // write
  byte fl = FONT_LARGE;
  osd.setPanel(x, y);    
  osd.openPanel(); 
  osd.write(fl+(v/100));
  osd.write(fl+((v%100)/10));
  osd.write(fl+((v%100)%10));  

  // write symbol
  if(symbol != NO_SYMBOL) osd.write(symbol);  
  osd.closePanel();    
}


/**
  * (DrawFourDigitValue) 
  */

void DrawFourDigitValue(byte x, byte y, long v, byte bsymbol, byte asymbol, int fl) {
  // verify
  if(v < 0 || v > 9999) return;
  

  osd.setPanel(x, y);    
  osd.openPanel(); 
  
  // write symbol
  if(bsymbol != NO_SYMBOL) osd.write(bsymbol); 
  
  // write numbers
  osd.write(fl+(v/1000));
  osd.write(fl+((v%1000)/100));
  osd.write(fl+(((v%1000)%100)/10));
  osd.write(fl+((v%100)%10));

  // write symbol
  if(asymbol != NO_SYMBOL) osd.write(asymbol);  
  osd.closePanel();    
}


/**
  * (GetUnitSymbol)
  */
  
byte GetUnitSymbol(float unit, boolean panel) {
  
  if(unit == UNIT_LENGTH_FT) return panel ? 0x68 : 0x6a;
  if(unit == UNIT_LENGTH_MI) return panel ? 0xec : 0x6c; 
  if(unit == UNIT_LENGTH_KM) return panel ? 0x67 : 0x6b;
  if(unit == UNIT_LENGTH_M) return panel ? 0x66 : 0x69;  
  if(unit == UNIT_LENGTH_NM) return panel ? 0xec : 0x64;
  
  return GetUnitSpeedSymbol(unit, panel);
}

byte GetUnitSpeedSymbol(float unit, boolean panel) {
  
  if(unit == UNIT_SPEED_MS) return panel ? 0x63 : NO_SYMBOL;
  if(unit == UNIT_SPEED_KMH) return panel ? 0x62 : NO_SYMBOL;
  if(unit == UNIT_SPEED_MPH) return panel ? 0x61 : NO_SYMBOL;
  if(unit == UNIT_SPEED_KN) return panel ? 0x64 : NO_SYMBOL;
  return NO_SYMBOL; 
}

/**
  * (DrawDistance) draws a distance with four digits
  */

void DrawDistance(byte x, byte y, float value, byte symbol) {
  
  // calculate large number
  float large = fabs(value * UNIT_DISTANCE_LARGE);
  boolean islarge = large >= 1;
  
  // assign
  if(islarge)  value = large;
  
  // validate
  value = (value < 0) ? 0 : (islarge && value > 99.9 ? 99.9 : (value > 9999 ? 9999 : value)); 
  
  // show distance based if its in the small or large range
  if(islarge) {
      osd.setPanel(x, y);
      osd.openPanel();
      osd.write(symbol);
      osd.writefloat(value, value < 10 ? 2 : 1);
      osd.write(GetUnitSymbol(UNIT_DISTANCE_LARGE));
      osd.closePanel();
  } else {
    DrawFourDigitValue(x, y, fabs(value * UNIT_DISTANCE), symbol, GetUnitSymbol(UNIT_DISTANCE), FONT_SMALL);
  }
}


/**
  * (DrawFancyHeading) 
  */
  
void DrawFancyHeading(byte x, byte y, long d) {
  if(d >= 16 || d < 0) d = 0;
  osd.setPanel(x, y);    
  osd.openPanel();
  osd.write(0x50 + d);  
  osd.closePanel();
}


/* (DrawOneSmallValue) Draws a one value */
void DrawOneSmallValue(byte x, byte y, int n) {
  int fs = FONT_SMALL;
  osd.setPanel(x, y);    
  osd.openPanel();
  osd.write(fs+n);
  osd.closePanel();  
}


/* (DrawNumber) Draws a number on the screen with filler etc */
void DrawNumber(byte x, byte y, int v, int d, int mi, int ma, int font) {
 // prepare
 if(v<mi) v = mi; if(v>ma) v = ma;
 // open panel
 osd.setPanel(x, y);
 osd.openPanel();
 // calc
 int l = (int)log10(d);
 for(int i=0;i<d;i++) {
    int j = pow(10, (d - i - 1));
    d = (int)v/j;
    osd.write(font+d);
    //v = v % jl;   
 }
 osd.closePanel();
}

/* (DrawBattery) Draws the Battery Status */
void DrawBattery(byte x, byte y, float voltage, byte type, byte mode) {
  
  if(voltage < 2) return;
  
  // calculate voltage
  float maxVoltage = (type + 1) * CELL_MAX_VOLTAGE,
        minVoltage = (type + 1) * CELL_MIN_VOLTAGE;
  
  // calculate percentage
  byte p = 100 - (((maxVoltage - voltage) * 100) / (maxVoltage - minVoltage));
  
  // sanity check
  p = p > 100 ? 100 : (p < 0 ? 0 : p);
  
  // set symbol
  byte symbol = SYMBOL_BATTERY_0;
  
  if(p > 90) {
    symbol = SYMBOL_BATTERY_100; 
  } else if (p > 60) {
    symbol = SYMBOL_BATTERY_60;   
  } else if (p > 30) {
    symbol = SYMBOL_BATTERY_30;      
  }
  
  // draw text
  osd.setPanel(x, y);
  osd.openPanel();
  osd.write(symbol);
  
  if(mode == 1) {
    p = p > 99 ? 99 : p;
    osd.write(FONT_SMALL + (p/10));
    osd.write(FONT_SMALL + (p%10));
    osd.write(SYMBOL_PERCSMALL); 
  } else {
    osd.writefloat(voltage, 1);
  } 
  osd.closePanel();    
}

/**
  * (DrawBatteryAlert)
  */

void DrawBatteryAlert(bool show, float voltage, byte type) {
  
  // show
  show = show ? ((type + 1) * CELL_ALERT_VOLTAGE) < voltage : false;
  
  CustomMessageAlert(show, "LOW BATTERY", LAYOUT_LOWVOLT_X, LAYOUT_LOWVOLT_Y, false);
        
}

/**
  * (DrawTimer) Draws a Timer Control
  */
  
void DrawTimer(byte x, byte y, unsigned long time, byte symbol, boolean small) {  
  if(time < 0) time = 0;
  
  // parse time
  int im = time / 1000;

  // get minutes
  int minutes = im / 60;
  int seconds = im % 60;

  // draw osd
  osd.setPanel(x, y);    
  osd.openPanel();

  // write symbol
  if(symbol != NO_SYMBOL) osd.write(symbol);

  // write minutes and seconds
  osd.write((small ? 0xe0 : 0x25)+(minutes/10));
  osd.write((small ? 0xe0 : 0x25)+(minutes%10));
  osd.write(0x97);
  osd.write((small ? 0xe0 : 0x25)+(seconds/10));
  osd.write((small ? 0xe0 : 0x25)+(seconds%10));
  osd.closePanel();
}


/** 
  * (DrawBox) Draws a box with simple elements
  */

void DrawBox(int x, int y, int w, int h) {
  
  for (int cy = 0; cy < h; cy++) { // top and bottom y
    // draw 
    if(cy == 0 || cy == (h-1)) {
      // draw lines
      for(int cx = 0; cx < w; cx++) {
        osd.writexy(x + cx, y + cy, (cy == 0) ? 0xea : 0xeb);
      }
    } else {
      osd.writexy(x, y + cy, 0xec);
      osd.writexy(x + (w-1), y + cy, 0xed);
    }
  }
  
  // draw four corners
  osd.writexy(x, y, 0xfa);
  osd.writexy(x + (w-1), y, 0xfb);
  osd.writexy(x, y + (h-1), 0xfc);
  osd.writexy(x + (w-1), y + (h-1), 0xfd); 
}

/**
  * (DrawLabelBox) Draws a box but with labels
  */
  
void DrawLabelBox(byte x, byte y, byte w, byte h, byte ll, byte lr) {
  
  DrawBox(x, y, w, h);
  
  if(ll != NO_SYMBOL) osd.writexy(x, y + 1, ll);
  if(lr != NO_SYMBOL) osd.writexy(x + (w) - 1, y + 1, lr); 

}  
  
/** 
  * (DrawLogo) Draws the FPV Tools Logo
  */
void DrawLogo() {
  osd.setPanel(vma(9, -1),vma(8, 1));    
  osd.openPanel();
  for(byte i = 0; i < 13; i++) {
    osd.write(0xb0 + i);
  }
  osd.closePanel();
  
  osd.setPanel(vma(12, -1), vma(6, 1));
  osd.openPanel(); 
  
  for(byte i = 0; i < 7; i++) {
    osd.write(0xc0 + i);
  }
  osd.closePanel();
}


/**
  * (DrawCoordinates) 
  */
  
void DrawCoordinates(byte x, byte y, float value, byte prec, byte symbol) {
  osd.setPanel(x, y);
  osd.openPanel();
  if(symbol != NO_SYMBOL) osd.write(symbol);
  
  float v = value < 0 ? -1 * value : value;
  
  if(value > 0) osd.write(CHAR_CLEAR);
  if(v < 100) osd.write(CHAR_CLEAR);
  if(v < 10)osd.write(CHAR_CLEAR);
 
   osd.writefloat(value, prec);
   osd.closePanel();    
}

/**
  * (vma) adjust based on video mode
  */

int vma(byte v, byte a) {
  return VIDEO_MODE == 0 ? v + a : v; 
}  



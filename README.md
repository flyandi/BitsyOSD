BitsyOSD
=======

BitsyOSD is a minimalistic OSD based on the works of ArduCam and minimNaza. It's intended to be used on the MinimOSD Hardware that can be purchased for less then $20 USD.


## Why another OSD?

There are plenty of options out there but I needed something very simple that just works and was small - I looked at all the other great projects which provide a lot of configurations and options but that was overkill for me. So I rewrote the codebase and created a fixed layout OSD that allows

## Video

Check out the video below for a quick introduction:

[![Video](https://github.com/FPVTools/BitsyOSD/blob/master/docs/bitsyosd-animation.gif)](http://www.youtube.com/watch?v=92WtLzoAQVY)

## Features

Currently BitsyOSD implements the following values in a fixed layout that is partially configurable or can be easily adapted via the code. 

* Speed 
* Altitude (ASL, AGL)
* Heading
* Simple Variometer
* Traveled Distance
* Home Heading Indicator 
* Home Distance
* Flight Timer
* GPS Statuses
* GPS Coordinates

**Please be aware that BitsyOSD doesn't have any outside configuration possibilities and all modifications need to be done via the code base**

![Screen1](https://github.com/FPVTools/BitsyOSD/blob/master/docs/00123333.jpg)
![Screen2](https://github.com/FPVTools/BitsyOSD/blob/master/docs/bitsyosd-main-screen.png)

## Get Started

You don't need to be an code expert but I assume that you have the following things ready to go:

* Arduino IDE installed on your computer
* NodeJS installed
* GIT installed
* MinimOSD hardware
* USB FTDI TTL serial adapter
* Custom GPS Cable as described on [https://code.google.com/p/minnazaosd/wiki/SolderGPS]


Next you need to download this project. Navigate to a directory where you want to keep the BitsyOSD code and clone the project via git.

```shell
git clone https://github.com/FPVTools/BitsyOSD
````

A quick hint: Connect the MinimOSD to a TV if you want to see whats going on with your MinimOSD during the setup process.


### Install Libraries

BitsyOSD is using several libraries that need to be installed to your Arduino IDE. Copy and paste all of the libraries found in ```libraries/``` to your Arduino's IDE libraries folder and restart the Arduino IDE. 

Learn more how to install libraries in Arduino at [http://arduino.cc/en/Guide/Libraries]



### Upload the font

BitsyOSD is using a custom font that needs to be uploaded to the MinimOSD. The entire font upload process is outside of the main code base to keep the size small. 

**Note: You need to redo this process if the font set changes in future firmware updates**

Connect the MinimOSD via the USB FTDI TTL serial adapter to your computer and upload the file ```font/fontupload/fontupload.ino``` via the Arduino IDE to the MinimOSD. If you have a screen connected, you should be able to see the current font set on it.

Open a command console and navigate to the folder ```font/```. Execute the following command and follow the on-screen instructions.

```shell
node uploadfont.js
```

This process may take some time and you should see the new font set on your display if you have a screen connected.

![Font](https://github.com/FPVTools/BitsyOSD/blob/master/docs/bitsyosd-font-upload.jpg)

### Upload the firmware

Make sure the MinimOSD is connected to your computer via the USB FTDI TTL serial adapter. Open the file ```BitsyOSD/BitsyOSD.ino``` and click ```Upload``` in the Arduino IDE.

If you installed the libraries as well uploaded the font correctly, you now have a working MinimOSD with BitsyOSD. 



## License

Copyright (c) 2015.  All rights reserved.
Author: Andreas Schwarz
Version: 1.0

Uses base code and sources from these projects:

ArduCam Project http://arducam-osd.googlecode.com
minimNAZA http://minnazaosd.googlecode.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
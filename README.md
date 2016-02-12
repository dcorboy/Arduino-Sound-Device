# Arduino-Sound-Device

Arduino-Sound-Device is a music and sound-effects device I created using the Music Shield V1.0 product apparently produced by [LinkSprint](http://www.linksprite.com/).

## Motivation

The product appears to no longer be supported and the libraries that are available are all out of date. Since I had managed to update them and add some functionality, I wanted to share this with others so they can take advantage of an inexpensive, good-quality music shield.

Most of the available information can be found on the [SeeedStudio Wiki page](http://www.seeedstudio.com/wiki/Music_Shield_V1.0). My changes are based on the Music_v1_14 libraries that you can get in their original form [here](http://www.seeedstudio.com/wiki/File:Music_v1_14.zip).

## Installation

The **LSMusicShield** folder should be able to be installed as a normal Arduino library. My current application appears as the included example.

## Hardware Integration

When the shield is installed normally, no pins are available without an intermediate proto-shield. By using the schematic available on the SeeedStudio wiki page and some experimentation, I was able to determine the minimum number of pins needed to operate the board.

### Standard Pins

The following pins are required for the basic operation of the board. These should be connected to the corresponding Arduino pins, as if the shield were in place.

* +5V and one of the ground pins
* The 6 pins of the SPI header
* The 4 analog pins A0, A1, A2, A3
* Digital pin D10
* The GND pin (next to D13)

### IR Integration

To use the infra-red remote feature, I connect the signal pin of a VS1838B to **Pin D7**.
To blink an LED when IR is received, I connect an LED and resistor to **Pin D6**

### Serial Integration

For serial control, I set up a SoftwareSerial port on **Pins D2 (Rcv) & D3 (Tx)** so you can connect your external device there, along with a ground connection.

### Image of Connections

![Mounted with Connections](https://github.com/dcorboy/Arduino-Sound-Device/mounted-connections.jpg "Mounted with Connections")

## Usage

TODO

Explain the software interface for playing tracks

Explain the IR system

Explain the serial play method

## License

I do not own the rights to the underlying libraries.

[GNU General Public License](http://www.gnu.org/licenses/)

&copy; Copyright 2016 Dave Corboy <dave@corboy.com>

These *modifications* to the LinkSprite library constitute the Arduino-Sound-Device software.

Arduino-Sound-Device is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Arduino-Sound-Device is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

If you did not receive a copy of the GNU General Public License
along with Arduino-Sound-Device, see <http://www.gnu.org/licenses/>.
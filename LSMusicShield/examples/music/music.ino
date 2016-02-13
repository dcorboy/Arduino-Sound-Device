
#include <avr/io.h>
#include "config.h"
#include "filesys.h"
#include "player.h"
#include "vs10xx.h"
#include "record.h"
#include <SoftwareSerial.h>
#include <IRremote.h>

#define IR_INPUT  7
#define IR_LED    6

#define CMD_BUFR_SIZ 12

/////////////// for sound command serial interface ////////////////
#define ID0 0xC0
#define ID1 0x5D
#define HELLO   0x00  // used for testing
#define SETVOL  0x01  // data byte specifies volume
#define VOLUP   0x02  // data byte specifies amount, 0 means +5
#define VOLDN   0x03  // data byte specifies amount, 0 means +5
#define PLAYTRK 0x04  // data byte specifies track number

SoftwareSerial ctrlSerial(2, 3);  // pin2 - Rx, pin3 - Tx
IRrecv IRRecv(IR_INPUT, IR_LED);
decode_results results;

void setup()
{
  Serial.begin(9600);
  ctrlSerial.begin(4800);
  IRRecv.enableIRIn(); // Start the receiver

  InitSPI();
  InitIOForVs10xx();
  //InitIOForKeys();
  //InitIOForLEDs();
  InitFileSystem();

  Mp3Reset();
  SetVolume(20);
  Serial.println(F("Enter track number to play (1-9)"));

}

void loop() {
  if (Serial.available() > 0) {
    byte input = Serial.read();
    switch (input) {
      case 'r' :
        Mp3Reset();
        break;
      case 'v' :
        Serial.print(F("Current volume: "));
        Serial.println(GetVolume());
        break;
      case '+' :
        SetVolume(GetVolume() - 10);
        Serial.print(F("Current volume: "));
        Serial.println(GetVolume());
        break;
      case '-' :
        SetVolume(GetVolume() + 10);
        Serial.print(F("Current volume: "));
        Serial.println(GetVolume());
        break;
      default :
        {
          byte num = input - '0';
          if (num >= 1 && num <= 9) {
            Serial.print(F("Playing track: "));
            Serial.println(num);
            PlayTrack(num);
          }
        }
    }
  }
  check_serial_control();
  check_IR_control();
}

bool decode_serial_command(byte (&bufr)[CMD_BUFR_SIZ]) {
  if (ctrlSerial.available() > 0) {
    byte i = 0;
    delay(100);
    byte len = ctrlSerial.available();
    byte olen = len;
    while (len--) {
      bufr[i++] = ctrlSerial.read();
    }
    bufr[i] = 0;
    if (olen == 4 && bufr[0] == ID0 && bufr[1] == ID1) {
      return true;
    }
  }
  return false;
}

void check_serial_control() {
  byte command[CMD_BUFR_SIZ];
  if (decode_serial_command(command)) {
    byte cmd = command[2];
    byte data = command[3];
    switch (cmd) {
      case HELLO :
        Serial.println(data);
        break;
      case PLAYTRK :
        Serial.print(F("Control play track: "));
        Serial.println(data);
        PlayTrack(data);
        break;
      case SETVOL :
        SetVolume(data);
        break;
      case VOLUP :
        SetVolume(GetVolume() - (data == 0 ? 5 : data));
        break;
      case VOLDN :
        SetVolume(GetVolume() + (data == 0 ? 5 : data));
        break;
    }
  }
}

// these are simple FNV hashes of the raw data, so they don't mean anything but should be consistent and unique
#define IR_ZERO    0xC101E57B
#define IR_ONE     0x9716BE3F
#define IR_TWO     0x3D9AE3F7
#define IR_THREE   0x6182021B
#define IR_FOUR    0x8C22657B
#define IR_FIVE    0x488F3CBB
#define IR_SIX     0x449E79F
#define IR_SEVEN   0x32C6FDF7
#define IR_EIGHT   0x1BC0157B
#define IR_NINE    0x3EC3FC1B 
#define IR_VOL_UP  0xE5CFBD7F
#define IR_VOL_DN  0xA3C8EDDB

void check_IR_control() {
  if (IRRecv.decode(&results)) {
    byte track = 0;
    switch(results.value) {
      case IR_NINE :  // These all FALL THROUGH so watch out
        track++;
      case IR_EIGHT :
        track++;
      case IR_SEVEN :
        track++;
      case IR_SIX :
        track++;
      case IR_FIVE :
        track++;
      case IR_FOUR :
        track++;
      case IR_THREE :
        track++;
      case IR_TWO :
        track++;
      case IR_ONE :
        track++;
      case IR_ZERO :
        PlayTrack(track);
        break;
      case IR_VOL_UP :
        SetVolume(GetVolume() - 10);
        break;
      case IR_VOL_DN :
        SetVolume(GetVolume() + 10);
        break;
    }
    Serial.println(results.value, HEX);
    IRRecv.resume(); // Receive the next value
  }
}


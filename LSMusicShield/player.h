#ifndef __PLAYER_H
#define __PLAYER_H

#include "ui.h"



extern unsigned char playStop;
extern playingstatetype playingState;

extern unsigned char currentFile;

void SetVolume(byte volume);
byte GetVolume();
void Play();
void PlayTrack(byte track);
//void CheckPlay();
void CheckKey();

#endif


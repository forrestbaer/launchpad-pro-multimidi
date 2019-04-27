#ifndef octave_h
#define octave_h

#include "app.h"
#include "visual/color.h"

color octaveColor(u8 which);
void ChangeOctave(bool isUp, u8 whichOctave);
void ChangeOctaveUp(u8 index, u8 value);
void ChangeOctaveDown(u8 index, u8 value);
void ChangeOctaveUp2(u8 index, u8 value);
void ChangeOctaveDown2(u8 index, u8 value);

#endif /* octave_h */

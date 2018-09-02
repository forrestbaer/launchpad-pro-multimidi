#ifndef note_func_h
#define note_func_h

#include "app.h"

u8 roundrobin;

void MakeStar(u8 index, u8 value);
void DoNote(u8 index, u8 value);
void rrUpCheck();
void CircuitDrum(u8 index, u8 value);
void ChangeOctave(bool isUp);
void ChangeOctaveUp(u8 index, u8 value);
void ChangeOctaveDown(u8 index, u8 value);

#endif /* note_func_h */

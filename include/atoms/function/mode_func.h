#ifndef mode_func_h
#define mode_func_h

#include "app.h"

//Mode is like state but may also have more specifics attached to it, like an instrument

void ModeFunc(LpState setting, u8 index, u8 value);
void ModePlay(u8 index, u8 value);
void ModeOff(u8 index, u8 value);
void ModeScaleArp(u8 index, u8 value);
void ModeCircuitpad(u8 index, u8 value);

#endif /* mode_func_h */

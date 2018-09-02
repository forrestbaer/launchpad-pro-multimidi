#ifndef circuitpad_h
#define circuitpad_h

#include "app.h"
#include "environment/state.h"

void ToggleDrum1(u8 index, u8 value);
void ToggleDrum2(u8 index, u8 value);
void ToggleDrum3(u8 index, u8 value);
void ToggleDrum4(u8 index, u8 value);
// void ToggleCircuitpad(u8 index, u8 value);
// void ToggleCircuitpadBack(u8 index, u8 value);
void build_circuitpad();
void state_circuitpad(StateEvent msg, u8 index, u8 value);

#endif /* circuitpad_h */

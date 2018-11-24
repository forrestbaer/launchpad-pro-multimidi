#ifndef circuitpad_h
#define circuitpad_h

#include "app.h"
#include "environment/state.h"

void SampleTuner(u8 index, u8 value);
void ToggleDrum(u8 index, u8 value);
void build_circuitpad();
void build_samplechromatic();
void state_circuitpad(StateEvent msg, u8 index, u8 value);

#endif /* circuitpad_h */

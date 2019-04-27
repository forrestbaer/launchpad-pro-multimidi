#ifndef digitonepad_h
#define digitonepad_h

#include "app.h"
#include "state/state.h"

void ToggleDigitoneState(u8 index, u8 value);
void build_digitonepad();
void build_digitone_delay();
void build_digitone_chorus();
void build_digitone_reverb();
void build_digitone_lfo();
void state_digitonepad(StateEvent msg, u8 index, u8 value);

#endif /* digitonepad_h */

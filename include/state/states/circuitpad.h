#ifndef circuitpad_h
#define circuitpad_h

#include "app.h"
#include "state/state.h"

void SampleTuner(u8 index, u8 value);
void DrumPads64(u8 index, u8 value);
void MicrotonalSetup(u8 index, u8 value);
void MicrotonalPlay(u8 index, u8 value);
void ToggleDrum(u8 index, u8 value);
void clear_circuitpad();
void build_circuitpad_header();
void build_circuitpad();
void build_samplechromatic();
void build_microtonal_setup();
void recursiveScan(u8 *cnt, u8 *oct);
void build_microtonal_play();
void state_circuitpad(StateEvent msg, u8 index, u8 value);

#endif /* circuitpad_h */

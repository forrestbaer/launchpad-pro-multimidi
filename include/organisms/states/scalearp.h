#ifndef scalearp_h
#define scalearp_h

#include "app.h"
#include "environment/state.h"

void ToggleScaleArp(u8 index, u8 value);
void ToggleScaleArpBack(u8 index, u8 value);
void build_scale_arp();
void build_scale_arp_vertical();
void state_scalearp(StateEvent msg, u8 index, u8 value);

#endif /* scalearp_h */

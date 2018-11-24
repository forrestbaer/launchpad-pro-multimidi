#ifndef mastercontrol_h
#define mastercontrol_h

#include "app.h"
#include "environment/state.h"

void Togglemastercontrol(u8 index, u8 value);
void TogglemastercontrolBack(u8 index, u8 value);
void SetChannelGroup1(u8 index, u8 value);
void SetChannelGroup2(u8 index, u8 value);
void build_mastercontrol();
void build_drumbrute_impact();
void rebuild_mastercontrol();
//void build_mastercontrol_vertical();
void state_mastercontrol(StateEvent msg, u8 index, u8 value);

#endif /* mastercontrol_h */

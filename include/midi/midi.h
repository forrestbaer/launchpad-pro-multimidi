#ifndef midi_h
#define midi_h

#include "app.h"

void midi_both(u8 status, u8 data1, u8 data2);
void midi_din(u8 status, u8 data1, u8 data2);
void midi_usb(u8 status, u8 data1, u8 data2);
u8 velocity_adjust (u8 value);
u8 get_midi_channel(u8 vInstSlot);
void midi_note(u8 channel, u8 note, u8 value);
void midi_cc(u8 channel, u8 ccmsg, u8 value);
void midi_pc(u8 channel, u8 pcmsg);
void midi_start();
void midi_stop();
void midi_continue();

#endif /* midi_h */

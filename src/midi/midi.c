#include "midi/midi.h"
#include "visual/surface.h"

void midi_both(u8 status, u8 data1, u8 data2) {
    hal_send_midi(DINMIDI, status, data1, data2);
    hal_send_midi(USBMIDI, status, data1, data2);
}
void midi_din(u8 status, u8 data1, u8 data2) {
    hal_send_midi(DINMIDI, status, data1, data2);
}
void midi_usb(u8 status, u8 data1, u8 data2) {
    hal_send_midi(USBMIDI, status, data1, data2);
}
u8 velocity_adjust (u8 value) {
    u8 adj = 0;
    if (value == 0) { return 0; }
    switch(memory_store[MEM_VELOCITY]) {
      case 0:
        return value;
      break;
      case 1:
        if (value < 63) {
          return value / 2;
        } else {
          adj = 32 + (value - 63) * 1.5;
          if ( adj > 126) {
            adj = 127;
          }
          return adj;
        }
      break;
      case 2:
        adj = value + 40;
        if ( adj > 126) {
          adj = 127;
        }
        return adj;
      break;
      case 3:
        return 90;
      case 4:
        return 127;
      break;
    }
    return value;
}

u8 get_midi_channel(u8 vInstSlot) {
    return memory_store[10+vInstSlot];
}

void midi_note(u8 channel, u8 note, u8 value) {
    midi_both(NOTEON | get_midi_channel(channel), note, velocity_adjust(value));
}
void midi_cc(u8 channel, u8 ccmsg, u8 value) {
    midi_both(CC | get_midi_channel(channel), ccmsg, value);
}
void midi_pc(u8 channel, u8 pcmsg) {
    midi_both(PROGRAMCHANGE | get_midi_channel(channel), pcmsg, 0);
}
void midi_start() {
    midi_both(MIDISTART, 0, 0);
}
void midi_stop() {
    midi_both(MIDISTOP, 0, 0);
}
void midi_continue() {
    midi_both(MIDICONTINUE, 0, 0);
}

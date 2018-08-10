#include "atoms/midi/midi.h"

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
void midi_note(u8 channel, u8 note, u8 value) {
    midi_both(NOTEON | channel, note, value);
}
void midi_cc(u8 channel, u8 ccmsg, u8 value) {
    midi_both(CC | channel, ccmsg, value);
}
void midi_pc(u8 channel, u8 pcmsg) {
    midi_both(PROGRAMCHANGE | channel, pcmsg, 0);
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

#include "util/note_func.h"
#include "midi/midi.h"
#include "visual/surface.h"
#include "state/state.h"


color octaveColor(u8 which) {
    color c = {0,0,0};
    switch (octave[which]) {  // could move to color.c
      case 0:
        c.r = 7;
      break;
      case 1:
        c.r = 7;
        c.b = 10;
      break;
      case 2:
        c.r = 8;
        c.b = 20;
      break;
      case 3:
        c.r = 10;
        c.g = 10;
        c.b = 10;
      break;
      case 4:
        c.g = 10;
      break;
      case 5:
        c.g = 10;
        c.b = 10;
      break;
      case 6:
        c.r = 20;
        c.g = 10;
      break;
      case 7:
        c.r = 40;
      break;
      case 8:
        c.r = 40;
        c.g = 40;
      break;
      case 9:
        c.r = 40;
        c.g = 40;
        c.b = 40;
      break;
      case 10:
        c.r = 40;
        c.b = 63;
        c.g = 50;
      break;
    }
    return c;
}

void ChangeOctave(bool isUp, u8 whichOctave) {
    if (isUp) {
      if (octave[whichOctave] + 1 > 10) { return; }
      octave[whichOctave]++;
    } else {
      s8 s8octave = octave[whichOctave];
      if (s8octave - 1 < 0) { return; }
      octave[whichOctave]--;
    }
    memory_store[5+whichOctave] = octave[whichOctave];  // put in the store but not saved until other save events
    color c = octaveColor(whichOctave);
    if ( whichOctave == 0 ) {
      change_color(91, c.r, c.g, c.b);
      change_color(92, c.r, c.g, c.b);
      (*stateMachine)(EVENT_REDRAW, 0, 0); 
    } else if ( whichOctave == 1) {
      change_color(1, c.r, c.g, c.b);
      change_color(2, c.r, c.g, c.b);
    }
    //(*stateMachine)(EVENT_REDRAW, 0, 0);  // wasteful redraw
    //kill_channel_notes(0);  // old way before heldnotes
}

void ChangeOctaveUp(u8 index, u8 value) {
    if (value > 0 ) {
      (*ChangeOctave)(true, 0);
    }
}

void ChangeOctaveDown(u8 index, u8 value) {
    if (value > 0 ) {
      (*ChangeOctave)(false, 0);
    }
}

void ChangeOctaveUp2(u8 index, u8 value) {
    if (value > 0 ) {
      (*ChangeOctave)(true, 1);
    }
}

void ChangeOctaveDown2(u8 index, u8 value) {
    if (value > 0 ) {
      (*ChangeOctave)(false, 1);
    }
}

#include "music/kill.h"
#include "midi/midi.h"
#include "visual/pad.h"
#include "visual/surface.h"


void kill_channel_notes( u8 midichannel ) {
  midi_both(CC | midichannel, 123, 0 );
  // pads_held_count = 0;
}

void kill_most_notes() {  // we're going to do all except Ch 10 (Drums)
  // midi_both_nonloop(CC | channel_lookup(0), 120, 0 ); // TODO: Check if this is correct!?!?! Should be CC to turn off all SOUNDS.
  // //it seems that the loop to manually turn off all is slow performance
  // pads_held_count = 0;
}

void kill_held_notes() { // a more caring kill function ;)
  for (u8 kdx = 0; kdx < BUTTON_COUNT; kdx++) {
    if ( heldnotes[kdx].note != -1 ) {
      midi_note(heldnotes[kdx].channel, heldnotes[kdx].note, 0);
    }
    heldnotes[kdx].note = -1;
    heldnotes[kdx].channel = -1;
  }
}
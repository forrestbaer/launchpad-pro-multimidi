#include "molecules/music/kill.h"

void kill_channel_notes( u8 midichannel ) {
  // midi_both_nonloop(CC | channel_lookup(midichannel), 123, 0 );
  // pads_held_count = 0;
}

void kill_most_notes() {  // we're going to do all except Ch 10 (Drums)
  // midi_both_nonloop(CC | channel_lookup(0), 120, 0 ); // TODO: Check if this is correct!?!?! Should be CC to turn off all SOUNDS.
  // //it seems that the loop to manually turn off all is slow performance
  // pads_held_count = 0;
}

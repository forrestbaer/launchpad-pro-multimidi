#include "music/arp.h"

// This takes the sequence 0,1,2,3,etc. and turns it into the Diatonic Step of Arpeggio Triads = 0,2,4,7,9,11,14, etc.
// probably simple math for this, but couldn't boil it down yet. Probably / and % combo... yep.....UPDATE: Boiled DOWN!!! Nice!
u8 arp_step_triad(u8 increment) {
  return ((increment / 3) * 7) + ((increment % 3) * 2);
}

// This takes the sequence 0,1,2,3,etc. and turns it into the 2 R-3-5-R sets  = 0,2,4,7,7,9,11,14,
// or really just 0,2,4,7 then 0,2,4,7 again and again
// because of the exception in this, i don't think simple math will do it.
u8 arp_step_mcp(u8 increment) {
  if ( increment > 3 ) {
    increment -= 4;
  }
  return ((increment / 3) * 7) + ((increment % 3) * 2);
}

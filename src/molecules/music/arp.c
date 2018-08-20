#include "molecules/music/arp.h"

// This takes the sequence 0,1,2,3,etc. and turns it into the Diatonic Step of Arpeggio Triads = 0,2,4,7,9,11,14, etc.
// probably simple math for this, but couldn't boil it down yet. Probably / and % combo... yep.....UPDATE: Boiled DOWN!!! Nice!
u8 arp_step_triad(u8 increment) {
  return ((increment / 3) * 7) + ((increment % 3) * 2);
}

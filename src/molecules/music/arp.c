#include "molecules/music/arp.h"

// This takes the sequence 0,1,2,3,etc. and turns it into the Diatonic Step of Arpeggio Triads = 0,2,4,7,9,11,14, etc.
// probably simple math for this, but couldn't boil it down yet. Probably / and % combo... yep.
u8 arp_step_triad(u8 increment) {
  return ((increment / 3) * 7) + ((increment % 3) * 2);

  // switch (increment) {  // remember, these are diatonic increments
  // case 0:
  //   return 0;
  // break;
  // case 3:
  //   return 7;
  // break;
  // case 6:
  //   return 14;
  // break;
  // case 9:
  //   return 21;
  // break;
  // case 12:
  //   return 28;
  // break;
  // case 1:
  //   return 2;
  // break;
  // case 4:
  //   return 9;
  // break;
  // case 7:
  //   return 16;
  // break;
  // case 10:
  //   return 23;
  // break;
  // case 13:
  //   return 30;
  // break;
  // case 2:
  //   return 4;
  // break;
  // case 5:
  //   return 11;
  // break;
  // case 8:
  //   return 18;
  // break;
  // case 11:
  //   return 25;
  // break;
  // case 14:
  //   return 32;
  // break;
  // }
  // return increment;
}

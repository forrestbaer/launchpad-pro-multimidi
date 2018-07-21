#include "molecules/time/animation.h"

u8 ledloop (u8 in) {
  if ( in > 127 ) { in -= 127; }  // a form of rough error handling
  if ( in < 64 ) {
    return in;
  } else {
    return 63 - (in - 64);
  }
}

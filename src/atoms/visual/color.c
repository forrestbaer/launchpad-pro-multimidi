#include "atoms/visual/color.h"

// given a simple 0 to 127 input, make an interesting range of color output
color colorRanger(u8 input, u8 type) {
    color rtnColor = {input / 2, input / 2, input / 2 };
    switch (type) {
        case 0: //start cold blue, then green, to add red, to full white
          rtnColor.r = 0;
          rtnColor.g = 0;
          if ( input > 93 ) {
            rtnColor.r = (input - 94) * 4;
          }
          if ( input > 32 ) {
            rtnColor.g = (input - 33) * 2;
          }
        break;
        case 1: //yellow to orange to red
          rtnColor.b = 0;
          rtnColor.g = 63 - (input / 2);
          rtnColor.r = 63;
        break;
        default:

        break;
    }
    return rtnColor;
}

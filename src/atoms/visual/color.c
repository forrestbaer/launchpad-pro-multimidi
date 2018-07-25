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
        case 2: // r to y to g to cyan to b to p to r...not really yet. got to find the math for this. but it looks cool anyway!
            if ( input < 32 ) {
              rtnColor.r = 63 - input * 2;
              rtnColor.g = input * 2;
              rtnColor.b = 0;
            } else if ( input >= 32 && input < 63 ) {
              rtnColor.r = 0;
              rtnColor.g = 63 - (input - 32) * 2;
              rtnColor.b = (input - 32) * 2;
            } else if ( input >= 63 && input < 95 ) {
              rtnColor.r = (input - 63) * 2;
              rtnColor.g = 0;
              rtnColor.b = 63 - (input - 63) * 2;
            } else {
              rtnColor.r = 63;
              rtnColor.g = 0;
              rtnColor.b = 0;
            }

        break;
        default:

        break;
    }
    return rtnColor;
}

// given a simpler 0 to 7 input, make a range of color output
color color8(u8 input, u8 type) {
    color rtnColor = {63,63,63};
    if ( type == 0 ) {
      switch (input) {
        case 0:
          rtnColor.r = 63;
          rtnColor.g = 0;
          rtnColor.b = 0;
        break;
        case 1:
          rtnColor.r = 63;
          rtnColor.g = 20;
          rtnColor.b = 0;
        break;
        case 2:
          rtnColor.r = 63;
          rtnColor.g = 54;
          rtnColor.b = 0;
        break;
        case 3:
          rtnColor.r = 0;
          rtnColor.g = 44;
          rtnColor.b = 0;
        break;
        case 4:
          rtnColor.r = 0;
          rtnColor.g = 44;
          rtnColor.b = 44;
        break;
        case 5:
          rtnColor.r = 0;
          rtnColor.g = 0;
          rtnColor.b = 63;
        break;
        case 6:
          rtnColor.r = 32;
          rtnColor.g = 0;
          rtnColor.b = 63;
        break;
        case 7:
          rtnColor.r = 63;
          rtnColor.g = 0;
          rtnColor.b = 63;
        break;
      }
    }
    return rtnColor;
}

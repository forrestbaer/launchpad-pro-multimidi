#include "molecules/visual/pad.h"

u8 directional(Direction whichDir, u8 fromPad) { //simple func to give pad above, below, left or right of current one (plus Diagonal)
  // can use IF EVEN then Not Diagonal
  u8 rtnPad = 0;  // rtnPad of 0 means invalid to get a real pad in this direction
  switch(whichDir) {
      case DIR_TL:
          if (fromPad + 10 < 100 && fromPad % 10 > 0) {
            rtnPad = fromPad + 9;
          }
          if ( fromPad == 81) {
            rtnPad = 0;
          }
      break;
      case DIR_UP:
          if (fromPad + 10 < 100) {
            rtnPad = fromPad + 10;
          }
          if (fromPad == 80 || fromPad == 89 ) {
            rtnPad = 0;
          }
      break;
      case DIR_TR:
          if (fromPad + 10 < 100 && fromPad % 10 < 9) {
            rtnPad = fromPad + 11;
          }
          if (fromPad == 88) {
            rtnPad = 0;
          }
      break;
      case DIR_RIGHT:
          if (fromPad % 10 < 9) {
            rtnPad = fromPad + 1;
          }
          if (fromPad == 9 || fromPad == 99) {
            rtnPad = 0;
          }
      break;
      case DIR_BR:
          if (fromPad - 10 > 0 && fromPad % 10 < 9) {
            rtnPad = fromPad - 9;
          }
          if (fromPad == 18) {
            rtnPad = 0;
          }
      break;
      case DIR_DOWN:
          if (fromPad - 10 > 0) {
            rtnPad = fromPad - 10;
          }
          if (fromPad == 10 || fromPad == 19) {
            rtnPad = 0;
          }
      break;
      case DIR_BL:
          if (fromPad - 10 > 0 && fromPad % 10 > 0) {
            rtnPad = fromPad - 11;
          }
          if (fromPad == 11) {
            rtnPad = 0;
          }
      break;
      case DIR_LEFT:
          if (fromPad % 10 > 0) {
            rtnPad = fromPad - 1;
          }
          if (fromPad == 91 ) {
            rtnPad = 0;
          }
      break;
      case DIR_NUM:
      break;
  }
  return rtnPad;
}

#include "visual/pad.h"
#include "visual/surface.h"
#include "time/timer.h"
#include "midi/midi.h"

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


void recrsvDirFill(u8 dirInt, u8 index, u8 recrsvDepth) { //recursive Directional Line Paint
  u8 rtnPad = directional(dirInt, index); // basically go 1 of 8 directions and fill in color that way until hit the edge
  if (rtnPad != 0) {
    u8 variance = animCnt + 20 * recrsvDepth;
    if (variance > 95 ) {
      variance -= 95;
    }
    color clr = colorRanger(animCnt+variance, 2);
    hal_plot_led(TYPEPAD, rtnPad, clr.r, clr.g, clr.b );
    recrsvDirFill(dirInt, rtnPad, recrsvDepth + 1);
  }
}

void recrsvDirClear(u8 dirInt, u8 index) { //recursive Directional Line Clear
  u8 rtnPad = directional(dirInt, index); // basically go 1 of 8 directions and CLEAR color that way until hit the edge
  if (rtnPad != 0) {
    hal_plot_led(TYPEPAD, rtnPad, grid_colors[rtnPad].r, grid_colors[rtnPad].g, grid_colors[rtnPad].b );
    recrsvDirClear(dirInt, rtnPad);
  }
}

// see pad.h for simple summary of "why" this pattern `function` and `Filled`

void DoMore(u8 setting, u8 index, u8 value) {
    if ( value > 0 ) {
      hal_plot_led(TYPEPAD, index, value / 2, value / 2, value / 2);
      for ( u8 cdx=0; cdx < DIR_NUM; cdx++ ) {
        u8 rtnPad = directional(cdx, index);
        if (rtnPad != 0) {
            color clr = color8(cdx, 0);
            hal_plot_led(TYPEPAD, rtnPad, clr.r * value / 63, clr.g * value / 63, clr.b * value / 63 );
            u8 rtnPad2 = directional(cdx, rtnPad);
            if (rtnPad2 != 0) {
                hal_plot_led(TYPEPAD, rtnPad2, clr.r * value / 63, clr.g * value / 63, clr.b * value / 63 );
            }
        }
      }
    } else {
      hal_plot_led(TYPEPAD, index, grid_colors[index].r, grid_colors[index].g, grid_colors[index].b );
      for ( u8 cdx=0; cdx < DIR_NUM; cdx++ ) {
        u8 rtnPad = directional(cdx, index);
        if (rtnPad != 0) {
            hal_plot_led(TYPEPAD, rtnPad, grid_colors[rtnPad].r, grid_colors[rtnPad].g, grid_colors[rtnPad].b  );
            u8 rtnPad2 = directional(cdx, rtnPad);
            if (rtnPad2 != 0) {
                hal_plot_led(TYPEPAD, rtnPad2, grid_colors[rtnPad2].r, grid_colors[rtnPad2].g, grid_colors[rtnPad2].b  );
            }
        }
      }
    }
}

void FilledDoMore(u8 index, u8 value) {  // This is to demo that a broad function "DoMore" can be set up but the Array holds Functions with more defined behavior for each Array item to create a grid of varying but similar functionality
    (*DoMore)(69, index, value);
}

void DoSpiral(u8 setting, u8 index, u8 value) {
    if (value > 0 ) {
      for ( u8 idx = 0; idx < 8; idx++) {
        color clr = color8(idx, 0);
        particle p = {directional(idx, index), clr.r * value / 63, clr.g * value / 63, clr.b * value / 63, idx, 1, 0};
        addParticle(p);
      }
    }
}

void FilledDoSpiral(u8 index, u8 value) {
    (*DoSpiral)(23, index, value);
}

void DoLeft(u8 setting, u8 index, u8 value) {
    if (value > 0 ) {
        particle p = {directional(7, index), 22, 0, 44, 7, 0, 0};
        addParticle(p);
    }
}

void FilledDoLeft(u8 index, u8 value) {
    (*DoLeft)(23, index, value);
}

void DoNoteTest(u8 setting, u8 index, u8 value) {
    midi_note(0 | setting, index, value);
    if (value > 0 ) {
        particle p = {directional(3, index), 44, 44, 44, 3, 0, 0};
        addParticle(p);
    }
}

void FilledDoNoteTest(u8 index, u8 value) {
    (*DoNoteTest)(0, index, value);
}

void DoNoteBeams(u8 setting, u8 index, u8 value) {
    midi_note(0 | setting, index, value);
    if (value > 0 ) {
        recrsvDirFill(1, index, 0);
        recrsvDirFill(3, index, 0);
        recrsvDirFill(5, index, 0);
        recrsvDirFill(7, index, 0);
    } else {
        recrsvDirClear(1, index);
        recrsvDirClear(3, index);
        recrsvDirClear(5, index);
        recrsvDirClear(7, index);
    }
}

void FilledDoNoteBeams(u8 index, u8 value) {
    (*DoNoteBeams)(0, index, value);
}

void DoStar(u8 setting, u8 index, u8 value) {
    midi_note(0 | setting, index, value);
    if (value > 0 ) {
        particle p = {directional(3, index), 33, 33, 63, 3, 0, 0};
        addParticle(p);
        particle r1 = {directional(3, index+1), 33, 33, 63, 3, 0, 0};
        addParticle(r1);
        particle r2 = {directional(3, index+2), 33, 33, 63, 3, 0, 0};
        addParticle(r2);
        particle l = {directional(7, index), 33, 33, 63, 7, 0, 0};
        addParticle(l);
        particle l1 = {directional(7, index-1), 33, 33, 63, 7, 0, 0};
        addParticle(l1);
        particle l2 = {directional(7, index-2), 33, 33, 63, 7, 0, 0};
        addParticle(l2);
        particle u = {directional(1, index), 33, 33, 63, 1, 0, 0};
        addParticle(u);
        particle u1 = {directional(1, index+10), 33, 33, 63, 1, 0, 0};
        addParticle(u1);
        particle u2 = {directional(1, index+20), 33, 33, 63, 1, 0, 0};
        addParticle(u2);
        particle d = {directional(5, index), 33, 33, 63, 5, 0, 0};
        addParticle(d);
        particle d1 = {directional(5, index-10), 33, 33, 63, 5, 0, 0};
        addParticle(d1);
        particle d2 = {directional(5, index-20), 33, 33, 63, 5, 0, 0};
        addParticle(d2);
    }
}

void FilledDoStar(u8 index, u8 value) {
    (*DoStar)(23, index, value);
}

void Pressure(u8 setting, u8 index, u8 value) {
  if ( value > 64 ) {
      for ( u8 cdx=0; cdx < DIR_NUM; cdx++ ) {
          u8 rtnPad = directional(cdx, index);
          if (rtnPad != 0) {
              hal_plot_led(TYPEPAD, rtnPad, (value - 64), 0, 0 );
          }
      }
  }
  if ( value <= 64 ) {
    for ( u8 cdx=0; cdx < DIR_NUM; cdx++ ) {
        u8 rtnPad = directional(cdx, index);
        if (rtnPad != 0) {
            hal_plot_led(TYPEPAD, rtnPad, grid_colors[rtnPad].r, grid_colors[rtnPad].g, grid_colors[rtnPad].b );
        }
    }
  }
}

void FilledPressure(u8 index, u8 value) {
    (*Pressure)(23, index, value);
}

void NullFunction(u8 index, u8 value) {
    return; //Do nothing! But receives parameters to avoid error.
}

u8 pianoDraw(u8 interval) {
  // sequential placement of the next key in the keyboard/piano

  //boiling the non-mathematical design of the Piano Keyboard into a function (or the grid based equivalent)
  //is tough, with no purely math way of doing it. This is the most systematic way I could think up.
  //its pretty good, and needs to work with another loop to place the keys.
  s8 totalShift = 0; // this builds thru each progressive piano key, by going thru the chromatic
  for ( u8 idx = 0; idx < interval; idx++ ) {
      s8 shiftType = 11; //means goes diagonal right
      if ( idx == 4 || idx == 11 ) {
        shiftType = 1;  //means goes to right
      } else if ( idx == 1 || idx == 3 || idx == 6 || idx == 8 || idx == 10 ) {
        shiftType = -10; //means goes down
      }
      totalShift += shiftType;
  }

  return totalShift;
}

// This and convGridto64() help match an array[64] easy to map to the assumed 8x8 grid
u8 conv64toGrid( u8 orig64 ) { //a new test, i think this is valid
  // Example Use: Give me 0 - 63 and return pad# to meet that. ie: 11,12,18,21,22,28,,,,88
    u8 row8 = ((orig64 / 8) + 1) * 10;
    u8 col8 = (orig64 % 8) + 1;
    if ( (row8 >= 10) && (row8 < 90) && (col8 >= 1) && (col8 < 9) ) {
      return row8 + col8;
    } else {
      return 99;   // will catch this as bad on other side. ...or ignored as pad 99 is nothing
    }
}

u8 convGridto64( u8 origGrid ) {
  // Example Use: Give me 11,12,18 (Pad Grid Index),,,,88 and return 0, 1, 3, ,,,,63
    u8 ones = (origGrid % 10) - 1;
    u8 tens = (origGrid / 10) - 1;
    if ( (ones >= 0) && (ones < 8) && (tens >= 0) && (tens < 8) ) {
      return ones + tens * 8;
    } else {
      return 99;  // will catch this as bad on other side.
    }
}

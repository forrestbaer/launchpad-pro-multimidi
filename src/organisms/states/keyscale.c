#include "organisms/states/keyscale.h"
#include "environment/surface.h"
#include "organisms/visual/columnset.h"
#include "organisms/visual/rowset.h"
#include "molecules/visual/pad.h"
#include "molecules/music/diatonic.h"
#include "atoms/function/note_func.h"

void SetSubModePlay(u8 index, u8 value) {
    if (value > 0) {
       build_scaleplay();
    }
}

void SetSubModeUser(u8 index, u8 value) {
    if (value > 0) {
        build_keyscale();
    }
}

void SetKey(u8 index, u8 value) {
    if (value > 0) {
        for ( u8 cdx = 31; cdx < 49; cdx++ ) { //clean up loop
            // simplest to find the one that's ON and switch it off
            if ( grid_params[cdx].p1 == 1 ) {
              change_color(cdx, grid_colors[cdx].r / 4, grid_colors[cdx].g / 4, grid_colors[cdx].b / 4);
              grid_params[cdx].p1 = 0;
            }
        }
        keyscale = grid_params[index].p2;
        grid_params[index].p1 = 1;
        change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void SetModal(u8 index, u8 value) {
    if (value > 0) {
      for ( u8 rdx = 1; rdx < 3; rdx++ ) {
        for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          u8 pad = rdx*10 + cdx;
          if ( grid_params[pad].p1 == 1 ) {
            change_color(pad, grid_colors[pad].r / 4, grid_colors[pad].g / 4, grid_colors[pad].b / 4);
            grid_params[pad].p1 = 0;
          }
        }
        modal = grid_params[index].p2;
        grid_params[index].p1 = 1;
        change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
      }
    }
}

void SetOffset(u8 index, u8 value) {
    if (value > 0) {
        for ( u8 odx = 1; odx < 8; odx++ ) { //clean up loop
            // simplest to find the one that's ON and switch it off
            u8 pad = 80 + odx;
            if ( grid_params[pad].p1 == 1 ) {
              change_color(pad, grid_colors[pad].r / 4, grid_colors[pad].g / 4, grid_colors[pad].b / 4);
              grid_params[pad].p1 = 0;
            }
        }
        scaleOffset = grid_params[index].p2;
        grid_params[index].p1 = 1;
        change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void SetHideNonscale( u8 index, u8 value ) {
    if (value > 0) {
      for ( u8 hdx = 1; hdx < 3; hdx++ ) {  // 2 buttons to toggle Hide Non-scale notes or show (dark) but can hit the accidentals
          u8 pad = 70 + hdx;
          if ( grid_params[pad].p1 == 1 ) {
            change_color(pad, grid_colors[pad].r / 4, grid_colors[pad].g / 4, grid_colors[pad].b / 4);
            grid_params[pad].p1 = 0;
          }
      }
      hideNonscale = grid_params[index].p2;
      grid_params[index].p1 = 1;
      change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void build_keyscale() {
    for ( u8 cdx = 1; cdx < 9; cdx++ ) {  //clear out for purity ;)
      for ( u8 rdx = 1; rdx < 9; rdx++ ) {
        grid_params[cdx*10+rdx].p2 = 0;
        change_color(cdx*10+rdx, 0, 0, 0);
        grid_func[cdx*10+rdx] = &NullFunction;
      }
    }
    color dimWhite = {11,11,11};
    color dimPurple = {6,0,11};
    color dimPink = {21,11,12};
    color dimGold = {11,7,0};
    color dimGreen = {0,11,0};
    for ( u8 pdx = 0; pdx < 12; pdx++ ) { // draw and function set the root note selector.
        u8 pad = 31 + pianoDraw(pdx);
        color curColor = dimWhite;
        if ( pad > 39 ) {
            curColor = dimPurple;
        }
        grid_func[pad] = &SetKey;
        if ( keyscale == pdx ) {
          grid_params[pad].p1 = 1; //checks if keyscale (global var) then it is on
          curColor.r *= 4;
          curColor.g *= 4;
          curColor.b *= 4;
        } else {
          grid_params[pad].p1 = 0; //toggled off by default
        }
        grid_params[pad].p2 = pdx; // this tells the function to set the key x chromatic notes from C
        change_color(pad, curColor.r, curColor.g, curColor.b);
    }
    for ( u8 rdx = 1; rdx < 3; rdx++ ) {  // draw and set the modal/scale selector (Circuit scales available)
      for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          u8 pad = rdx*10 + cdx;
          color curColor = dimPink;
          grid_func[pad] = &SetModal;
          if ( convGridto64(pad) == conv64toGrid(modal) ) {
            grid_params[pad].p1 = 1;
            curColor.r *= 4;
            curColor.g *= 4;
            curColor.b *= 4;
          } else {
            grid_params[pad].p1 = 0;
          }
          grid_params[pad].p2 = convGridto64(pad); // this tells the function to set the mode to the right one
          change_color(pad, curColor.r, curColor.g, curColor.b);
      }
    }
    for ( u8 odx = 1; odx < 8; odx++ ) {  // draw and set the scale offset factor (like LPP factory firmware)
        u8 pad = 80 + odx;
        color curColor = dimGold;
        grid_func[pad] = &SetOffset;
        if ( scaleOffset == odx-1 ) {
          grid_params[pad].p1 = 1;
          curColor.r *= 4;
          curColor.g *= 4;
          curColor.b *= 4;
        } else {
          grid_params[pad].p1 = 0;
        }
        grid_params[pad].p2 = odx-1; // this tells the function to set the mode to the right one
        change_color(pad, curColor.r, curColor.g, curColor.b);
    }
    for ( u8 hdx = 1; hdx < 3; hdx++ ) {  // 2 buttons to toggle Hide Non-scale notes or show (dark) but can hit the accidentals
        u8 pad = 70 + hdx;
        color curColor = dimGreen;
        grid_func[pad] = &SetHideNonscale;
        if ( scaleOffset == hdx-1 ) {
          grid_params[pad].p1 = 1;
          curColor.r *= 4;
          curColor.g *= 4;
          curColor.b *= 4;
        } else {
          grid_params[pad].p1 = 0;
        }
        grid_params[pad].p2 = hdx-1; // this tells the function to set the mode to the right one
        change_color(pad, curColor.r, curColor.g, curColor.b);
    }
    grid_func[96] = &SetSubModePlay;
    change_color(96, 0, 12, 44);
    grid_func[98] = &SetSubModeUser;
    change_color(98, 30, 20, 0);
    rowset_octave_mode_etc();
}

void build_scaleplay() { // also handle 7 overlap modes
    for ( u8 cdx = 1; cdx < 9; cdx++ ) {  //clear out for purity ;)
      for ( u8 rdx = 1; rdx < 10; rdx++ ) {
        grid_params[cdx*10+rdx].p2 = 0;
        change_color(cdx*10+rdx, 0, 0, 0);
        grid_func[cdx*10+rdx] = &NullFunction;
      }
    }
    // and Hide / Show non-scale notes (accidentals / chromatic notes not in scale)
    u8 totalpadcounter = 0; // goes from 0 to 63 for various needs
    u8 scalecounter = 1;  // the step in the current modal-scale, esp. for when hideNonscale is 1(true)
    u8 chromaticcounter = 0; // more for not hideNonscale (= 0)
    u8 octavecounter = 0; // also integrate octave selector from other Systems into this one.
    for ( u8 rdx = 1; rdx < 9; rdx++ ) {  // row/column may be better
      for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          //the way the scale mode works: 0 offset = octaves stacked vertically (in most cases)
          // 1 offset = 7th, then 2nd octave
          // 2 offset = 6th, 7th, then 2nd octave, etc.
          // green pad on dup'd notes

          u8 pad = rdx*10 + cdx;
          grid_func[pad] = &DoNoteMarked;
          grid_params[pad].p1 = 0;  // this is the midi channel TODO add changer for channel
          if (hideNonscale == 0) {
              grid_params[pad].p2 = totalpadcounter; // found out if not scale mode the layout is always the same on factory
              if ( chromaticcounter == 0 ) {
                change_color(pad, 33,33,33);
              } else if ( chromaticcounter == 2 || chromaticcounter == 4 || chromaticcounter == 5 || chromaticcounter == 7 ||
                          chromaticcounter == 9 || chromaticcounter == 11 ) {
                change_color(pad, 5, 30, 35);
              } else {
                change_color(pad, 0,0,0);
              }
              chromaticcounter++;
              if (chromaticcounter > 11) {
                chromaticcounter = 0;
              }
              totalpadcounter++;
          } else if (hideNonscale == 1) {  // "Scale Mode"
              grid_params[pad].p2 = scales[modal][scalecounter] + octavecounter*12;
              if (scalecounter == 1) {  // root note color
                change_color(pad, 33,33,33);
              } else {
                change_color(pad, 5, 30, 35);
              }
              scalecounter++;
              if ( scalecounter > scales[modal][0] ) {
                octavecounter++;
                scalecounter = 1;
              }
          }
      }
      //next row...
      octavecounter = rdx; // base setup with no offset
      scalecounter = 1; // base setup with no offset
      s8 adjust = 0; // backwards counting mechanism for doing offset.
      if ( scaleOffset > 0 ) {  // if any offset then...
        octavecounter--;  // lower octave
        adjust = scales[modal][0] + 1 - scaleOffset * (rdx);  // go to last note in scale and progressively back from that
        recursiveAdjust(&adjust, &octavecounter);  // made this recursive because on shorter scales it got used a lot more than anticipated
        scalecounter = adjust;  // commit final result to scalecounter
      }
    }
}

void recursiveAdjust(s8 *adj, u8 *oct) {
  if (*adj < 1) {
    *oct = *oct - 1; // some scales are short enough going back 2 octaves is heard of...
    *adj = scales[modal][0] + *adj; // if so, continue counting thru scale backwards
    recursiveAdjust(adj, oct);
  }
}

// attempt 1:.... there were some useful things in it.... could do non-scale mode but higlight the notes in scale
// u8 pad = rdx*10 + cdx;
// grid_func[pad] = &DoNote;
// grid_params[pad].p1 = 0;  // this is the midi channel
// if (hideNonscale == 0) {
//   grid_params[pad].p2 = totalpadcounter; // only this simple if not hideNonscale
// } else if (hideNonscale == 1) {
//   grid_params[pad].p2 = octavecounter + scales[modal][scalecounter];
// }
// if ( scalecounter >= scales[modal][0] ) {
//   scalecounter = 1;
//   chromaticcounter = 0;
//   octavecounter++;
// }
// if (scalecounter == 1 && chromaticcounter == 0) {  // root note color
//   change_color(pad, 33,33,33);
// } else if ( scales[modal][scalecounter] == chromaticcounter ) {
//   change_color(pad, 5, 30, 35);
// } else {
//   change_color(pad, 0,0,0);
// }
//
// if (hideNonscale == 0) {
//   chromaticcounter++;
//   if ( scales[modal][scalecounter+1] == chromaticcounter ) {
//     scalecounter++;
//   }
//   if ( chromaticcounter > 11 ) {
//     chromaticcounter = 0;
//     octavecounter++;
//   }
// } else if (hideNonscale == 1) {
//   scalecounter++;
//   chromaticcounter = scales[modal][scalecounter];
// }
//
// totalpadcounter++;


void state_keyscale(StateEvent msg, u8 index, u8 value) {
  switch (msg) {
    case EVENT_EXIT:
      exit_surface();
      break;
    case EVENT_ENTER:
      current_state = LP_KEYSCALE_MODE; // for side queries of state...?
      build_keyscale();
      break;
    case EVENT_INPUT:
      (*grid_func[index])(index, value);
      break;
    case EVENT_REDRAW:
    case EVENT_CLOCK:
    case EVENT_PRESSURE:
    case EVENT_MSG_COUNT:
      break;
  }
}

#include "organisms/states/keyscale.h"
#include "environment/surface.h"
#include "organisms/visual/columnset.h"
#include "organisms/visual/rowset.h"
#include "molecules/visual/pad.h"
#include "molecules/music/diatonic.h"
#include "atoms/function/note_func.h"
#include "atoms/midi/aftertouch.h"

void SetSubModePlay(u8 index, u8 value) {
    if (value > 0) {
       build_scaleplay();
       hal_write_flash(0, memory_store, 30); // another good place to save, often after lots of config work
    }
}

void SetSubModeUser(u8 index, u8 value) {
    if (value > 0) {
        build_keyscale();
    }
}

void SetSubModeSends(u8 index, u8 value) {
    if (value > 0) {
        build_midi_channels();
    }
}

void SetSubModeAftertouch(u8 index, u8 value) {
    if (value > 0) {
        build_aftertouch();
    }
}

void paint_mode_notes() {
    // given a key and mode/scale... give more indication on the "piano display" what notes are in scale
    color dimTeal = {0,16,6};
    color dimWhite = {11,11,11};
    color dimPurple = {6,0,11};

    for ( u8 pdx = 0; pdx < 12; pdx++ ) { // draw and function set the root note selector.
        u8 pad = 31 + pianoDraw(pdx);
        color curColor = dimWhite;
        if ( pad > 39 ) {
            curColor = dimPurple;
        }
        change_color(pad, curColor.r, curColor.g, curColor.b);
    }

    // root note already painted

    // make a test for the notes in scale

    for ( u8 sdx = 1; sdx <= scales[modal][0]; sdx++ ) {  // this will skip the root, allow each in scale
        // add root_note_number to scales[modal][sdx]
        u8 wk_note = keyscale + scales[modal][sdx];
        if ( wk_note > 11 ) {
            wk_note -= 12;
        }
        // then if over 11 subtract 12 (double-check), this = note_number
        u8 pad = 31 + pianoDraw(wk_note);
        if ( sdx == 1 ) {
          change_color(pad, 63,63,63);
        } else {
          change_color(pad, dimTeal.r, dimTeal.g, dimTeal.b);
        }
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
        memory_store[1] = grid_params[index].p2;
        grid_params[index].p1 = 1;
        change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
        paint_mode_notes();
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
      }

      // ADD simple TEST for if NOTE is in KEY and MODE, wrap around may be a trick.


      modal = grid_params[index].p2;
      memory_store[2] = grid_params[index].p2;
      grid_params[index].p1 = 1;
      change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
      paint_mode_notes();
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
        memory_store[3] = grid_params[index].p2;
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
      memory_store[4] = grid_params[index].p2;
      grid_params[index].p1 = 1;
      change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void SetAftertouch( u8 index, u8 value ) {
    if (value > 0) {
      for ( u8 hdx = 1; hdx < 5; hdx++ ) { 
          u8 pad = 80 + hdx;
          if ( grid_params[pad].p1 == 1 ) {
            change_color(pad, grid_colors[pad].r / 4, grid_colors[pad].g / 4, grid_colors[pad].b / 4);
            grid_params[pad].p1 = 0;
          }
      }
      memory_store[MEM_AFTERTOUCH] = grid_params[index].p2;
      grid_params[index].p1 = 1;
      change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void SetAftertouchCcOnes( u8 index, u8 value ) {
    if (value > 0) {
      for ( u8 hdx = 0; hdx < 10; hdx++ ) { 
          u8 pad = 10 + hdx;
          if ( grid_params[pad].p1 == 1 ) {
            change_color(pad, grid_colors[pad].r / 4, grid_colors[pad].g / 4, grid_colors[pad].b / 4);
            grid_params[pad].p1 = 0;
          }
      }
      aft_cc_ones = grid_params[index].p2;
      // add 10 to create clear difference from the other modes of aftertouch
      memory_store[MEM_AFTERTOUCH] = 10 + aft_cc_hundreds * 100 + aft_cc_tens * 10 + aft_cc_ones;
      grid_params[index].p1 = 1;
      change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void SetAftertouchCcTens( u8 index, u8 value ) {
    if (value > 0) {
      for ( u8 hdx = 0; hdx < 10; hdx++ ) { 
          u8 pad = 20 + hdx;
          if ( grid_params[pad].p1 == 1 ) {
            change_color(pad, grid_colors[pad].r / 4, grid_colors[pad].g / 4, grid_colors[pad].b / 4);
            grid_params[pad].p1 = 0;
          }
      }
      aft_cc_tens = grid_params[index].p2;
      memory_store[MEM_AFTERTOUCH] = 10 + aft_cc_hundreds * 100 + aft_cc_tens * 10 + aft_cc_ones;
      grid_params[index].p1 = 1;
      change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void SetAftertouchCcHundreds( u8 index, u8 value ) {
    if (value > 0) {
      for ( u8 hdx = 0; hdx < 2; hdx++ ) { 
          u8 pad = 30 + hdx;
          if ( grid_params[pad].p1 == 1 ) {
            change_color(pad, grid_colors[pad].r / 4, grid_colors[pad].g / 4, grid_colors[pad].b / 4);
            grid_params[pad].p1 = 0;
          }
      }
      aft_cc_hundreds = grid_params[index].p2;
      memory_store[MEM_AFTERTOUCH] = 10 + aft_cc_hundreds * 100 + aft_cc_tens * 10 + aft_cc_ones;
      if ( memory_store[MEM_AFTERTOUCH] > 137 ) {  // Fixes input if over 127
          memory_store[MEM_AFTERTOUCH] = 137;
          aft_cc_ones = 7;
          aft_cc_tens = 2;
          for ( u8 adx = 0; adx < 10; adx++ ) { 
              u8 pad10 = 20 + adx;
              u8 pad1 = 10 + adx;
              change_color(pad1, 8,8,8);
              change_color(pad10, 8,6,4);
              grid_params[pad10].p1 = 0;
              grid_params[pad1].p1 = 0;
          }
          change_color(17, 8*4,8*4,8*4);
          change_color(22, 8*4,6*4,4*4);
          grid_params[17].p1 = 1;
          grid_params[22].p1 = 1;
      }
      grid_params[index].p1 = 1;
      change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void SetVelocityCurve(u8 index, u8 value) {
    if (value > 0) {
        for ( u8 odx = 1; odx < 6; odx++ ) { //clean up loop
            // simplest to find the one that's ON and switch it off
            u8 pad = odx*10;
            if ( grid_params[pad].p1 == 1 ) {
              change_color(pad, grid_colors[pad].r / 4, grid_colors[pad].g / 4, grid_colors[pad].b / 4);
              grid_params[pad].p1 = 0;
            }
        }
        velocityCurve = grid_params[index].p2;
        memory_store[7] = grid_params[index].p2;
        grid_params[index].p1 = 1;
        change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void SetMidiChannelSlot(u8 index, u8 value) {
    if (value > 0) {
      for ( u8 rdx = 7; rdx < 9; rdx++ ) {
        for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          u8 pad = rdx*10 + cdx;
          if ( grid_params[pad].p1 == 1 ) {
            change_color(pad, grid_colors[pad].r / 4, grid_colors[pad].g / 4, grid_colors[pad].b / 4);
            grid_params[pad].p1 = 0;
          }
        }
      }
      selectedSlot = grid_params[index].p2; // don't need to save this to memory
      // but do need to display the set Midi Channel for this slot below.

      color dimBlue = {0,0,11};
      for ( u8 rdx = 4; rdx < 6; rdx++ ) {
        for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          u8 pad = rdx*10 + cdx;
          change_color(pad, dimBlue.r, dimBlue.g, dimBlue.b); // "clear out" 
          if ( (rdx-4)*8 + cdx-1 == memory_store[10+selectedSlot] ) {  
            // the first math says boil down the 2 rows into a 0 to 15 equivalent
            // and match it to the Midi Channel in memory of the selectedSlot
            change_color(pad, dimBlue.r * 4, dimBlue.g * 4, dimBlue.b * 4);
          }
        }
      }

      grid_params[index].p1 = 1;
      change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void SetMidiChannel(u8 index, u8 value) {
    if (value > 0) {
      for ( u8 rdx = 4; rdx < 6; rdx++ ) {
        for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          u8 pad = rdx*10 + cdx;
          if ( grid_params[pad].p1 == 1 ) {
            change_color(pad, grid_colors[pad].r / 4, grid_colors[pad].g / 4, grid_colors[pad].b / 4);
            grid_params[pad].p1 = 0;
          }
        }
      }
      memory_store[10+selectedSlot] = convGridto64(index) - 24;
      grid_params[index].p1 = 1;
      change_color(index, grid_colors[index].r * 4, grid_colors[index].g * 4, grid_colors[index].b * 4);
    }
}

void clear_keyscale() {
    for ( u8 cdx = 0; cdx < 10; cdx++ ) {  //clear out for purity ;)
      for ( u8 rdx = 0; rdx < 10; rdx++ ) {
        grid_params[cdx*10+rdx].p2 = 0;
        change_color(cdx*10+rdx, 0, 0, 0);
        grid_func[cdx*10+rdx] = &NullFunction;
        grid_pres[cdx*10+rdx] = &NullFunction;
      }
    }
}

void build_keyscale() {
    clear_keyscale();

    color dimWhite = {11,11,11};
    color dimPurple = {6,0,11};
    color dimPink = {21,8,8};
    color dimGold = {11,7,0};
    color dimGreen = {0,11,0};
    color dimBlue = {0,0,11};
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
    paint_mode_notes();
    for ( u8 rdx = 1; rdx < 3; rdx++ ) {  // draw and set the modal/scale selector (Circuit scales available)
      for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          u8 pad = rdx*10 + cdx;
          color curColor = dimPink;
          grid_func[pad] = &SetModal;
          if ( pad == conv64toGrid(modal) ) {
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
        if ( hideNonscale == hdx-1 ) {
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
    for ( u8 vdx = 1; vdx < 6; vdx++ ) {  // 5 buttons to select Velocity Curve
        u8 pad = vdx*10;
        color curColor = dimBlue;
        grid_func[pad] = &SetVelocityCurve;
        if ( velocityCurve == vdx-1 ) {
          grid_params[pad].p1 = 1;
          curColor.r *= 4;
          curColor.g *= 4;
          curColor.b *= 4;
        } else {
          grid_params[pad].p1 = 0;
        }
        grid_params[pad].p2 = vdx-1; // this tells the function to set the mode to the right one
        change_color(pad, curColor.r, curColor.g, curColor.b);
    }
    build_keyscale_header_footer();
}

void build_scaleplay() { // also handle 7 overlap modes
    clear_keyscale();
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
          grid_pres[pad] = &AftertouchGeneral;
          grid_params[pad].p1 = 0;  // this is the midi channel TODO add changer for channel
          if (hideNonscale == 0) {
              grid_params[pad].p2 = totalpadcounter; // found out if not scale mode the layout is always the same on factory
              if ( chromaticcounter == 0 ) {
                change_color(pad, 33,33,33); // TODO: maybe make this color configurable too.
              } else if ( chromaticcounter == 2 || chromaticcounter == 4 || chromaticcounter == 5 || chromaticcounter == 7 ||
                          chromaticcounter == 9 || chromaticcounter == 11 ) {
                change_color(pad, 5, 30, 35); // TODO: make this color configurable!
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
                change_color(pad, 33,33,33);  // TODO: maybe make this color configurable too.
              } else {
                change_color(pad, 5, 30, 35);  // TODO: make this color configurable!
              }
              scalecounter++;
              if ( scalecounter > scales[modal][0] ) {
                octavecounter++;
                scalecounter = 1;
              }
          }
      }
      // next row...
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
    red_notes();
    build_keyscale_header_footer();
}

void build_midi_channels() {
    clear_keyscale();

    color dimGreen = {0,11,0};
    color dimBlue = {0,0,11};

    for ( u8 rdx = 7; rdx < 9; rdx++ ) {  // This is for selecting the Virtual Instrument to assign the MIDI Channel for
      for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          u8 pad = rdx*10 + cdx;
          color curColor = dimGreen;
          grid_func[pad] = &SetMidiChannelSlot;
          if ( pad == conv64toGrid(selectedSlot + 48)  ) {
            grid_params[pad].p1 = 1;
            curColor.r *= 4;
            curColor.g *= 4;
            curColor.b *= 4;
          } else {
            grid_params[pad].p1 = 0;
          }
          grid_params[pad].p2 = convGridto64(pad) - 48; // this tells the function to set the mode to the right one
          change_color(pad, curColor.r, curColor.g, curColor.b);
      }
    }

    for ( u8 rdx = 4; rdx < 6; rdx++ ) {  // With an active Virtual Instrument slot selected, press here to assign the midi channel
      for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          u8 pad = rdx*10 + cdx;
          color curColor = dimBlue;
          grid_func[pad] = &SetMidiChannel;
          // A little more complicated than this...
          // if ( pad == conv64toGrid(selectedSlot + 24)  ) {
          //   grid_params[pad].p1 = 1;
          //   curColor.r *= 4;
          //   curColor.g *= 4;
          //   curColor.b *= 4;
          // } else {
          //   grid_params[pad].p1 = 0;
          // }
          grid_params[pad].p2 = convGridto64(pad) - 24; // this tells the function to set the mode to the right one
          change_color(pad, curColor.r, curColor.g, curColor.b);
      }
    }
    
    build_keyscale_header_footer();
}

void build_aftertouch() {
    clear_keyscale();

    for ( u8 hdx = 1; hdx < 5; hdx++ ) {  // 4 buttons: Off, On Channel Aftertouch, On Poly Aftertouch, Pressure to CC
        u8 pad = 80 + hdx;
        color curColor = {0,11,0};
        grid_func[pad] = &SetAftertouch;
        if ( memory_store[MEM_AFTERTOUCH] == hdx-1 ) {
          grid_params[pad].p1 = 1;
          curColor.r *= 4;
          curColor.g *= 4;
          curColor.b *= 4;
        } else if ( memory_store[MEM_AFTERTOUCH] > 9 && hdx == 4 ) {
          grid_params[84].p1 = 1;
          pad = 84;
          curColor.r *= 4;
          curColor.g *= 4;
          curColor.b *= 4;
        } else {
          grid_params[pad].p1 = 0;
        }
        if ( pad == 84 ) {
          grid_params[pad].p2 = 11; // this will default the Map Pressure to CC to 1 (Mod Wheel)
        } else {
          grid_params[pad].p2 = hdx-1; // this tells the function to set the mode to the right one
        }
        change_color(pad, curColor.r, curColor.g, curColor.b);
    }

    for ( u8 odx = 0; odx < 10; odx++ ) {  // Pressure to CC Ones Digit
        u8 pad = 10 + odx;
        color curColor = {8,8,8};
        grid_func[pad] = &SetAftertouchCcOnes;
        if ( aft_cc_ones == odx ) {
          grid_params[pad].p1 = 1;
          curColor.r *= 4;
          curColor.g *= 4;
          curColor.b *= 4;
        } else {
          grid_params[pad].p1 = 0;
        }
        grid_params[pad].p2 = odx; 
        change_color(pad, curColor.r, curColor.g, curColor.b);
    }

    for ( u8 tdx = 0; tdx < 10; tdx++ ) {  // Pressure to CC Tens Digit
        u8 pad = 20 + tdx;
        color curColor = {8,6,4};
        grid_func[pad] = &SetAftertouchCcTens;
        if ( aft_cc_tens == tdx ) {
          grid_params[pad].p1 = 1;
          curColor.r *= 4;
          curColor.g *= 4;
          curColor.b *= 4;
        } else {
          grid_params[pad].p1 = 0;
        }
        grid_params[pad].p2 = tdx; 
        change_color(pad, curColor.r, curColor.g, curColor.b);
    }

    for ( u8 xdx = 0; xdx < 2; xdx++ ) {  // Pressure to CC Hundreds Digit
        u8 pad = 30 + xdx;
        color curColor = {4,6,8};
        grid_func[pad] = &SetAftertouchCcHundreds;
        if ( aft_cc_hundreds == xdx ) {
          grid_params[pad].p1 = 1;
          curColor.r *= 4;
          curColor.g *= 4;
          curColor.b *= 4;
        } else {
          grid_params[pad].p1 = 0;
        }
        grid_params[pad].p2 = xdx; 
        change_color(pad, curColor.r, curColor.g, curColor.b);
    }

    build_keyscale_header_footer();
}

void build_keyscale_header_footer() {
    grid_func[96] = &SetSubModePlay;
    change_color(96, 0, 12, 44);
    grid_func[98] = &SetSubModeUser;
    change_color(98, 30, 20, 0);
    grid_func[7] = &SetSubModeSends;
    change_color(7, 5, 10, 0);
    grid_func[6] = &SetSubModeAftertouch;
    change_color(6, 8, 0, 10);
    rowset_octave_mode_etc();
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
      hal_write_flash(0, memory_store, 30); // smart place to save here because when we leave this mode often is after lots of settings changed
      break;
    case EVENT_ENTER:
      current_state = LP_KEYSCALE_MODE;
      memory_store[0] = LP_KEYSCALE_MODE;
      hal_write_flash(0, memory_store, 30);
      build_keyscale();
      break;
    case EVENT_INPUT:
      (*grid_func[index])(index, value);
      break;
    case EVENT_PRESSURE:
      (*grid_pres[index])(index, value);
      break;
    case EVENT_REDRAW:
      build_scaleplay();
      // a new addition 1/1/2019 - based on Octave Change - draw in red notes for those exceeding midi note range
      
      //redraw_surface();
      break;
    case EVENT_CLOCK:
    case EVENT_MSG_COUNT:
      break;
  }
}

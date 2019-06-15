#include "state/states/circuitpad.h"
#include "visual/surface.h"
#include "visual/rowset.h"
#include "util/note_func.h"
#include "midi/aftertouch.h"
#include "music/kill.h"

void SampleTuner(u8 index, u8 value) {
    if (value > 0) {
      build_samplechromatic();
    }
}

void DrumPads64(u8 index, u8 value) {
    if (value > 0) {
      build_circuitpad();
    }
}

void MicrotonalSetup(u8 index, u8 value) {
    if (value > 0) {
      build_microtonal_setup();
    }
}

void MicrotonalPlay(u8 index, u8 value) {
    if (value > 0) {
      build_microtonal_play();
    }
}

void ToggleDrum(u8 index, u8 value) {
      if (value > 0) {
          if ( grid_params[index].p1 == 1 ) {
            grid_params[index].p1 = 0;
            color c = {0,9,0};
            hal_plot_led(TYPEPAD, index, 0,9,0);
            grid_colors[index] = c;
          } else {
            grid_params[index].p1 = 1;
            color c = {0,44,0};
            hal_plot_led(TYPEPAD, index, 0,44,0);
            grid_colors[index] = c;
          }
      }
}

void clear_circuitpad() {
    for ( u8 cdx = 0; cdx < 10; cdx++ ) {  //clear out all and reset properly
      for ( u8 rdx = 0; rdx < 10; rdx++ ) {
        grid_params[cdx*10+rdx].p2 = 0;
        change_color(cdx*10+rdx, 0, 0, 0);
        grid_func[cdx*10+rdx] = &NullFunction;
        grid_pres[cdx*10+rdx] = &NullFunction;
      }
    }
    kill_held_notes();
}

void build_circuitpad_header() {
    grid_func[96] = &SampleTuner;
    change_color(96, 0,0,50);
    grid_func[95] = &DrumPads64;
    change_color(95, 55,22,0);
    grid_func[97] = &MicrotonalSetup;
    change_color(97, 35,0,55);
    grid_func[98] = &MicrotonalPlay;
    change_color(98, 55,0,45);
}

void build_circuitpad() {
    clear_circuitpad();
    for ( u8 idx = 0; idx < 8; idx++ ) {
        rowset_circuit_fingerdrum(idx, 81 - idx * 10);
    }
    color c = {0,44,0};  // an example of a "One Off" button set-up... may be a better way but this is all I got right now.
    hal_plot_led(TYPEPAD, 89, 0,44,0);
    grid_func[89] = &ToggleDrum;
    grid_params[89].p1 = 1;  // p1 here is a toggle for on/off 1 = on, 0 = off - like boolean
    grid_colors[89] = c;
    hal_plot_led(TYPEPAD, 79, 0,44,0);
    grid_func[79] = &ToggleDrum;  // this was dumb, making 4 functions... p2 could have been the pad index or just use index ??
    grid_params[79].p1 = 1;
    grid_colors[79] = c;
    hal_plot_led(TYPEPAD, 69, 0,44,0);
    grid_func[69] = &ToggleDrum;
    grid_params[69].p1 = 1;
    grid_colors[69] = c;
    hal_plot_led(TYPEPAD, 59, 0,44,0);
    grid_func[59] = &ToggleDrum;
    grid_params[59].p1 = 1;
    grid_colors[59] = c;
    build_circuitpad_header();
}

const u8 drum_cc_pitch[33] = {
  0,1,2,4,6,7,9,10,12,14,16,19,
  21,23,26,29,32,35,38,42,46,50,54,59,
  64,69,74,80,86,92,99,106,114
};

void build_samplechromatic() {
    clear_circuitpad();

    for ( u8 idx = 0; idx < 32; idx++ ) {
        u8 pad = conv64toGrid(idx);
        color c = colorRanger(memory_store[MEM_COLOR_SCHEME]* 6, 4);
        if (idx == 0 || idx == 12 || idx == 24) {
          c = colorRanger(memory_store[MEM_COLOR_SCHEME]* 6, 5);
        }
        
        grid_params[pad].p1 = 0;
        grid_params[pad].p2 = drum_cc_pitch[idx];
        grid_func[pad] = &CircuitChromaticSample;
        grid_pres[pad] = &NullFunction;
        
        change_color(pad, c.r, c.g, c.b );
        //now do again for 2nd drum sample slot :) what a bargain!
        pad = conv64toGrid(idx+32);
        u8 color_scheme2 = MEM_COLOR_SCHEME+1;
        if (color_scheme2 > 14) { color_scheme2 -= 15;}
        c = colorRanger(memory_store[color_scheme2]* 6, 4);
        if (idx == 0 || idx == 12 || idx == 24) {
          c = colorRanger(memory_store[color_scheme2]* 6, 5);
        }
        
        grid_params[pad].p1 = 0;
        grid_params[pad].p2 = drum_cc_pitch[idx];
        grid_func[pad] = &CircuitChromaticSample2;
        grid_pres[pad] = &NullFunction;
        
        change_color(pad, c.r, c.g, c.b );
    }
    build_circuitpad_header();
}

void build_microtonal_setup() {
    clear_circuitpad();
    for ( u8 idx = 0; idx < 4; idx++ ) {
        rowset_microtonal_setup(idx, 11 + idx * 10);
    }
    // then make a way to turn off notes in the range to make "scales" within the microtonal system
    for ( u8 idx = 0; idx < 4; idx++ ) {
        rowset_microtonal_notes(idx, 51 + idx * 10);
    }
    build_circuitpad_header();
}

void recursiveScan(u8 *cnt, u8 *oct) {
  *cnt = *cnt + 1;
  if (*cnt >= microtonal_count) {
    *oct = *oct + 1;
    *cnt = 0;
    return;
  }
  if (microtonal_notes_on[*cnt] == 0) {
    recursiveScan(cnt, oct);
  }
}

void build_microtonal_play() {
    clear_circuitpad();
    rowset_octave_state_etc();
    color noteColor = colorRanger(memory_store[MEM_COLOR_SCHEME]* 6, 4);
    color rootColor = colorRanger(memory_store[MEM_COLOR_SCHEME]* 6, 5);
    u8 totalpadcounter = 0;
    u8 scalecounter = 0;  // the step in the current modal-scale
    u8 octavecounter = 0; // octave isn't 12 on microtonal
    // this helps make sure note 60 is always on an octave (important for the Jocko method on Circuit)
    u8 checker = microtonal_count;
    for ( u8 cdx = 2; cdx < 6; cdx++) {
      if (microtonal_count * cdx <= 60) {
        checker = microtonal_count * cdx;
      }
    }
    
    u8 rootCenter = 60 - checker;

    for ( u8 rdx = 1; rdx < 9; rdx++ ) {  // row/column may be better
      for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          u8 pad = rdx*10 + cdx;
          grid_func[pad] = &DoNoteMicrotonal;
          grid_pres[pad] = &AftertouchGeneral;
          grid_params[pad].p1 = 0; 
          grid_params[pad].p2 = octavecounter * microtonal_count + scalecounter + rootCenter;  // Root note will be there always

          if (scalecounter == 0) {  // root note color
            change_color(pad, rootColor.r, rootColor.g, rootColor.b); 
          } else {
            change_color(pad, noteColor.r, noteColor.g, noteColor.b);  
          }
          if ( octavecounter * microtonal_count + scalecounter + rootCenter > 127 ) {
            if ( memory_store[MEM_COLOR_SCHEME] != 0 ) {
                change_color(rdx*10+cdx, 50, 0, 0);
            } else {
                change_color(rdx*10+cdx, 63, 20, 0);
            }
            grid_func[pad] = &NullFunction;
          }

          recursiveScan(&scalecounter, &octavecounter); 
          totalpadcounter++;  // ? not used ?
      }
    }
    red_notes_microtonal();
    build_circuitpad_header();
}

void state_circuitpad(StateEvent msg, u8 index, u8 value) {
  switch (msg) {
    case EVENT_EXIT:
      exit_surface();
      break;
    case EVENT_ENTER:
      current_state = LP_CIRCUITPAD_STATE; // for side queries of state...? still haven't needed it anywhere - just may need it?
      memory_store[MEM_LAST_STATE] = LP_CIRCUITPAD_STATE;
      hal_write_flash(0, memory_store, 30);
      build_circuitpad();
      break;
    case EVENT_INPUT:
      (*grid_func[index])(index, value);
      break;
    case EVENT_REDRAW:
      build_microtonal_play();
      break;
    case EVENT_CLOCK:
    case EVENT_PRESSURE:
    case EVENT_MSG_COUNT:
      break;
  }
}

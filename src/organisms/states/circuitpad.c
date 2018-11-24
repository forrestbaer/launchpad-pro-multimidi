#include "organisms/states/circuitpad.h"
#include "environment/surface.h"
#include "organisms/visual/rowset.h"

void SampleTuner(u8 index, u8 value) {
    if (value > 0) {
      build_samplechromatic();
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


void build_circuitpad() {
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

    grid_func[96] = &SampleTuner;
    change_color(96, 0,0,50);
}

void build_samplechromatic() {
    for ( u8 idx = 0; idx < 8; idx++ ) {
        rowset_circuit_sampletune(idx, 81 - idx * 10);
    }
}

void state_circuitpad(StateEvent msg, u8 index, u8 value) {
  switch (msg) {
    case EVENT_EXIT:
      exit_surface();
      break;
    case EVENT_ENTER:
      current_state = LP_CIRCUITPAD_MODE; // for side queries of state...? still haven't needed it anywhere - just may need it?
      build_circuitpad();
      break;
    case EVENT_INPUT:
      (*grid_func[index])(index, value);
      break;
    case EVENT_REDRAW:
      redraw_surface();
      break;
    case EVENT_CLOCK:
    case EVENT_PRESSURE:
    case EVENT_MSG_COUNT:
      break;
  }
}

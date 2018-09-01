#include "organisms/states/scalearp.h"
#include "environment/surface.h"
#include "organisms/visual/columnset.h"
#include "organisms/visual/rowset.h"

void ToggleScaleArp(u8 index, u8 value) {
    if (value > 0) {
       build_scale_arp_vertical();
    }
}

void ToggleScaleArpBack(u8 index, u8 value) {
    if (value > 0) {
        build_scale_arp();
    }
}

void build_scale_arp() {
    for ( u8 idx = 0; idx < 8; idx++ ) {
        columnset_R35_arp(0, idx, 11 + idx); // basenote, mode, start pad (bottom)
    }
    rowset_octave_mode_etc();

    color c = {0,0,4};  // an example of a "One Off" button set-up... may be a better way but this is all I got right now.
    hal_plot_led(TYPEPAD, 98, 0,0,4);
    grid_func[98] = &ToggleScaleArp;
    grid_colors[98] = c;
}

void build_scale_arp_vertical() {
    for ( u8 idx = 0; idx < 8; idx++ ) {
        rowset_R35_arp(0, idx, 11 + idx * 10); // basenote, mode, start pad (bottom)
    }
    rowset_octave_mode_etc();

    color c = {0,0,4};
    hal_plot_led(TYPEPAD, 98, 0,0,4);
    grid_func[98] = &ToggleScaleArpBack;
    grid_colors[98] = c;
}

void state_scalearp(StateEvent msg, u8 index, u8 value) {
  switch (msg) {
    case EVENT_EXIT:
      exit_surface();
      break;
    case EVENT_ENTER:
      current_state = LP_SCALEARP_MODE; // for side queries of state...? still haven't needed it anywhere - just may need it?
      build_scale_arp();
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

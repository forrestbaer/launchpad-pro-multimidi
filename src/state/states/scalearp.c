#include "state/states/scalearp.h"
#include "visual/surface.h"
#include "visual/columnset.h"
#include "visual/rowset.h"

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
    rowset_octave_state_etc();

    grid_func[98] = &ToggleScaleArp;
    change_color(98, 0, 0, 4);
}

void build_scale_arp_vertical() {
    for ( u8 idx = 0; idx < 8; idx++ ) {
        rowset_R35_arp(0, idx, 11 + idx * 10); // basenote, mode, start pad (bottom)
    }
    rowset_octave_state_etc();

    grid_func[98] = &ToggleScaleArpBack;
    change_color(98, 0, 0, 4);
}

void state_scalearp(StateEvent msg, u8 index, u8 value) {
  switch (msg) {
    case EVENT_EXIT:
      exit_surface();
      break;
    case EVENT_ENTER:
      current_state = LP_SCALEARP_STATE;
      memory_store[MEM_LAST_STATE] = LP_SCALEARP_STATE;
      hal_write_flash(0, memory_store, 30);
      build_scale_arp();
      break;
    case EVENT_INPUT:
      (*grid_func[index])(index, value);
      break;
    case EVENT_REDRAW:
      //this is nice if it really is redrawing many of the pads,
      // but here it was not (only used for Octave redraw = 2 PADS!) so probably remove this...
    //   redraw_surface();
    //   break;
    case EVENT_PRESSURE:
        (*grid_pres[index])(index, value);
        break;
    case EVENT_CLOCK:
    case EVENT_MSG_COUNT:
      break;
  }
}

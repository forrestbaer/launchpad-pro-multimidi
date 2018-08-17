#include "organisms/states/setup.h"
#include "environment/surface.h"
#include "organisms/visual/columnset.h"

void build_scale_arp() {
    for ( u8 idx = 0; idx < 8; idx++ ) {
        columnset_R35_arp(48, idx, 11 + idx);
    }
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
    case EVENT_CLOCK:
    case EVENT_PRESSURE:
    case EVENT_MSG_COUNT:
      break;
  }
}

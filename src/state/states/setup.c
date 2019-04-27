#include "state/state.h"
#include "state/states/setup.h"
#include "visual/surface.h"

void state_setup(StateEvent msg, u8 index, u8 value) {
  switch (msg) {
    case EVENT_EXIT:
      exit_surface();
      break;
    case EVENT_ENTER:
      current_state = LP_SETUP_STATE;  // Not saved to the Flash Memory here, cause who wants to reboot to here?!?
      hal_plot_led(TYPEPAD, 13, 33, 0, 44);
      grid_func[13] = &StatePlay;
      hal_plot_led(TYPEPAD, 88, 33, 0, 44);
      grid_func[88] = &StateOff;
      hal_plot_led(TYPEPAD, 86, 0, 44, 0);
      grid_func[86] = &StateScaleArp;
      hal_plot_led(TYPEPAD, 81, 63, 8, 0);
      grid_func[81] = &StateMastercontrol;
      hal_plot_led(TYPEPAD, 18, 63, 44, 0);
      grid_func[18] = &StateCircuitpad;
      hal_plot_led(TYPEPAD, 96, 22, 63, 22);
      grid_func[96] = &StateKeyscale;
      hal_plot_led(TYPEPAD, 41, 0, 44, 44);
      grid_func[41] = &StateDigitonepad;
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

#include "organisms/states/setup.h"
#include "atoms/function/mode_func.h"
#include "environment/surface.h"

void state_setup(StateEvent msg, u8 index, u8 value) {
  switch (msg) {
    case EVENT_EXIT:
      exit_surface();
      break;
    case EVENT_ENTER:
      current_state = LP_SETUP_MODE;  // Not saved to the Flash Memory here, cause who wants to reboot to here?!?
      hal_plot_led(TYPEPAD, 13, 33, 0, 44);
      grid_func[13] = &ModePlay;
      hal_plot_led(TYPEPAD, 88, 33, 0, 44);
      grid_func[88] = &ModeOff;
      hal_plot_led(TYPEPAD, 86, 0, 44, 0);
      grid_func[86] = &ModeScaleArp;
      hal_plot_led(TYPEPAD, 81, 63, 8, 0);
      grid_func[81] = &ModeMastercontrol;
      hal_plot_led(TYPEPAD, 18, 63, 44, 0);
      grid_func[18] = &ModeCircuitpad;
      hal_plot_led(TYPEPAD, 96, 22, 63, 22);
      grid_func[96] = &ModeKeyscale;
      hal_plot_led(TYPEPAD, 41, 0, 44, 44);
      grid_func[41] = &ModeDigitonepad;
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

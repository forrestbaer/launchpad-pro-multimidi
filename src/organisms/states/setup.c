#include "organisms/states/setup.h"
#include "molecules/music/kill.h"
#include "molecules/visual/clear.h"
#include "atoms/function/clear_func.h"
#include "atoms/function/mode_func.h"
#include "environment/surface.h"

void state_setup(StateEvent msg, u8 index, u8 value) {
  switch (msg) {
    case EVENT_EXIT:
      kill_channel_notes(0);
      clear_leds();
      clear_all_functions();
      break;
    case EVENT_ENTER:
      current_state = LP_SETUP_MODE; // for side queries of state...?
      hal_plot_led(TYPEPAD, 13, 33, 0, 44);
      grid_func[13] = &ModePlay;
      hal_plot_led(TYPEPAD, 88, 33, 0, 44);
      grid_func[88] = &ModeOff;
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

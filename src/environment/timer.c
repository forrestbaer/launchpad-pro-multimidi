#include "app.h"
#include "environment/timer.h"
#include "environment/state.h"

u16 timeCounter = 0;

void core_clock() {
    //animated behavior is based on State. It may be further refined by Substate (Instrument, etc.)
    // there may be a better "function pointer" way to do this too
    timeCounter++;
    //if (timeCounter > 10000 ) { timeCounter = 0; }
    if ( timeCounter > 20 ) {
      (*stateMachine)(EVENT_CLOCK);
      timeCounter = 0;
    }
    // switch( current_state ) {
    //     case LP_PLAY_MODE:
    //
    //     break;
    //     case LP_OFF_MODE:
    //
    //     break;
    //     case LP_OVERLAY_MODE:
    //
    //     break;
    //     case LP_NUM_MODES:
    //     break;
    // }
}

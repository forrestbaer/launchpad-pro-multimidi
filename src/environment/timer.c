#include "app.h"
#include "environment/timer.h"
#include "environment/state.h"

u16 timeCounter = 0;
u8 animCnt = 0;

void core_clock() {
    //animated behavior is based on State. It may be further refined by Substate (Instrument, etc.)
    timeCounter++;
    animCnt++;
    //if (timeCounter > 10000 ) { timeCounter = 0; }
    if ( timeCounter > 20 ) {
      (*stateMachine)(EVENT_CLOCK, 0, 0);
      timeCounter = 0;
    }
    if ( animCnt > 100 ) {
      animCnt = 0;
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

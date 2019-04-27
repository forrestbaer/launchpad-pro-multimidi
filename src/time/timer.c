#include "app.h"
#include "time/timer.h"
#include "state/state.h"
#include "visual/particle.h"

u16 timeCounter = 0;
u8 animCnt = 0;

void core_clock() {
    //animated behavior is based on State. It may be further refined by Substate (Instrument, etc.)
    timeCounter++;
    animCnt++;
    if ( timeCounter > 20 ) {
      (*stateMachine)(EVENT_CLOCK, 0, 0);
      timeCounter = 0;
    }
    //cool, but a temp place for this method.
    if ( animCnt > 100 ) {
      animCnt = 0;
      moveParticles();
    }
    if ( animCnt == 50 ) {
      moveParticles();
    }
}

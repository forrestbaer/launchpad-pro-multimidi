#include "app.h"
#include "time/timer.h"
#include "state/state.h"
#include "visual/particle.h"
#include "midi/midi.h"

u8 timeCounter = 0;
u8 animCnt = 0;
d8 preciseTime = 500 / 24.0;

u8 twenthyfourth_tick = 0; 
u16 midiClockCounter = 0;

void core_clock() {
    //animated behavior is based on State. It may be further refined by Substate (Instrument, etc.)
    timeCounter++;
    animCnt++;

    // thought process...
    // 120 bpm = 500 ms per quarternote
    // 130 bpm = 462 ms per quarternote for context
    // midi clock sends 24 ticks per quarternote
    // so 500ms / 24 = 20.8333333
    // which is where we need the "preciseTime"

    // even though we are rounding here, with the twentyfourth_tick 
    // it gets it more accurate and it needs to be rounded to the millisecond anyway

    if ( round(preciseTime * twenthyfourth_tick) == midiClockCounter ) {
        if ( twenthyfourth_tick == 24 ) {
          twenthyfourth_tick = 0;
          midiClockCounter = 0;
          return;
        }
        // temporarily off until rest of system built...
        // midi_both(MIDITIMINGCLOCK, 0, 0);
        twenthyfourth_tick++;
    }
    midiClockCounter++;  // after so 0 gets a chance to run.

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

#include "molecules/event.h"
// #include "molecules/visual/pad.h"
// #include "environment/surface.h"
#include "environment/state.h"

void event_sysex(u8 port, u16 count) {
    //not sure yet what to do except maybe take in the stock firmware sysex to draw stuff.
}

void event_aftertouch(u8 index, u8 value) {
      // example - send poly aftertouch to MIDI ports
    (*stateMachine)(EVENT_PRESSURE, index, value);

}

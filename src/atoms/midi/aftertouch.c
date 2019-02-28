#include "atoms/midi/aftertouch.h" 
#include "atoms/midi/midi.h" 
#include "environment/surface.h"

void AftertouchGeneral(u8 index, u8 value) {
    if ( memory_store[MEM_AFTERTOUCH] == 0 ) {
        return; // no aftertouch
    } else if ( memory_store[MEM_AFTERTOUCH] == 1 ) {
        // channel aftertouch
        // should send greatest pressure value (specified in midi specification standard) - DOESN"T YET!
        midi_both(CHANNELAFTERTOUCH | get_midi_channel(grid_params[index].p1), value, 0);
    } else if ( memory_store[MEM_AFTERTOUCH] == 2 ) {
        // poly aftertouch
        u8 note = grid_params[index].p2 + octave[0] * 12 + keyscale;
        midi_both(POLYAFTERTOUCH | get_midi_channel(grid_params[index].p1), note, value);
    } else if ( memory_store[MEM_AFTERTOUCH] > 9 ) {
        // route pressure to CC value MEM_AFTERTOUCH - 10
        u8 bufferedAT = memory_store[MEM_AFTERTOUCH] - 10;
        if ( bufferedAT > 127 ) {
            bufferedAT = 127;
        }
        midi_cc(grid_params[index].p1, bufferedAT, value);
    }
}
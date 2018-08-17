#include "atoms/function/note_func.h"
#include "atoms/midi/midi.h"
#include "environment/surface.h"

void DoNote(u8 index, u8 value) {
    midi_note(grid_params[index].p1, grid_params[index].p2, value);
}

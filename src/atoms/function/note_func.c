#include "atoms/function/note_func.h"
#include "atoms/midi/midi.h"
#include "environment/surface.h"

void DoNote(u8 index, u8 value) {
    midi_note(grid_params[index].p1, grid_params[index].p2 + octave * 12 + keyscale, value);
}

void ChangeOctave(bool isUp) {
    if (isUp) {
      if (octave + 1 > 10) { return; }
      octave++;
    } else {
      s8 s8octave = octave;
      if (s8octave - 1 < 0) { return; }
      octave--;
    }
    //now redraw the octave Up/Down.... think about how to well-form this....
    // could be EVENT_REDRAW that the state uses to do a clear redraw without other actions
    // that would be clean because States that don't have Octaves could ignore this message

    //Also, either Kill Held Notes or form a system for Held Notes that ends them once released. The former is easier
}

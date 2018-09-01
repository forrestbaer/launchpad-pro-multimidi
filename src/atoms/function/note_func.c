#include "atoms/function/note_func.h"
#include "atoms/midi/midi.h"
#include "environment/surface.h"
#include "environment/state.h"
#include "molecules/music/kill.h"

void MakeStar(u8 index, u8 value) {
    color c = {0,0,0};
    if (value < 80) {
      c.r = 63;
      c.g = 23;
    } else if ( value >= 80 && value < 100 ) {
      c.g = 40;
      c.b = 50;
    } else {
      c.r = 33;
      c.g = 33;
      c.b = 63;
    }

    for (u8 sdx = 0; sdx < 3; sdx++) {
        particle r = {directional(3, index+sdx), c.r, c.g, c.b, 3, 0, 0};
        addParticle(r);
        particle l = {directional(7, index-sdx), c.r, c.g, c.b, 7, 0, 0};
        addParticle(l);
        particle u = {directional(1, index+(sdx*10)), c.r, c.g, c.b, 1, 0, 0};
        addParticle(u);
        particle d = {directional(5, index-(sdx*10)), c.r, c.g, c.b, 5, 0, 0};
        addParticle(d);
    }
}

void DoNote(u8 index, u8 value) {
    midi_note(grid_params[index].p1, grid_params[index].p2 + octave * 12 + keyscale, value);
    if (value > 60 ) {
        MakeStar(index, value);
    }
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
    color c = {33 + 3 * octave, 6 * octave + 3, 63};
    grid_colors[91] = c;
    grid_colors[92] = c;
    (*stateMachine)(EVENT_REDRAW, 0, 0);

    kill_channel_notes(0);
    // for future TODO: make better system of held notes store note they were sustaining so when released they can send the right note off message
}

void ChangeOctaveUp(u8 index, u8 value) {
    if (value > 0 ) {
      (*ChangeOctave)(true);
    }
}

void ChangeOctaveDown(u8 index, u8 value) {
    if (value > 0 ) {
      (*ChangeOctave)(false);
    }
}

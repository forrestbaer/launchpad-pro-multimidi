#include "atoms/function/note_func.h"
#include "atoms/midi/midi.h"
#include "environment/surface.h"
#include "environment/state.h"
#include "molecules/music/kill.h"

u8 roundrobin = 0;

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
    if (value > 0) {
        u8 note = grid_params[index].p2 + octave * 12 + keyscale;
        midi_note(grid_params[index].p1, note, value);
        heldnotes[index].note = note;  // heldnotes creates a management system for notes on and off that better handles change
        heldnotes[index].channel = grid_params[index].p1;
    } else {
        if ( heldnotes[index].note != -1 ) {
          midi_note(heldnotes[index].channel, heldnotes[index].note, value);
        }
        heldnotes[index].note = -1;
        heldnotes[index].channel = -1;
    }
    if (value > 60 ) {
        MakeStar(index, value);
    }
}

void rrUpCheck() {
    roundrobin++;
    if (roundrobin > 3 ) {
      roundrobin = 0;
    }
}

void CircuitDrum(u8 index, u8 value) {
    //now to complicate thing the grid_params for 89,79,69,59   p1 0 false, 1 true tell us if the roundrobin skips certain "Drum CHannels"
    u8 skiproundrobin[4] = {grid_params[89].p1, grid_params[79].p1, grid_params[69].p1, grid_params[59].p1};
    if ( skiproundrobin[0] == 0 && skiproundrobin[1] == 0 && skiproundrobin[2] == 0 && skiproundrobin[3] == 0) {
      return;  //if all are unselected then just stop! avoids bad loop
    }
    //found bug jamming on this.  if changed OPEN drum channels then this needs to sweep for if roundrobin is on a CLOSED channel

    if ( skiproundrobin[roundrobin] == 0 ) {
        rrUpCheck();
        if ( skiproundrobin[roundrobin] == 0 ) {
            rrUpCheck();
            if ( skiproundrobin[roundrobin] == 0 ) {
                rrUpCheck();
            }
        }
    }

    u8 staggereddrum[4] = {60,62,64,65};
    u8 patchselect[4] = {8,18,44,50};
    if ( value > 0 ) {
        midi_cc(9, patchselect[roundrobin], grid_params[index].p2);
        midi_note(9, staggereddrum[roundrobin], value);  // the NOTE OFF's are going to be off here. Another reason to need the Held Note Manager!
        heldnotes[index].note = staggereddrum[roundrobin];
        heldnotes[index].channel = 9;

        rrUpCheck();
        if ( skiproundrobin[roundrobin] == 0 ) {
            rrUpCheck();
            if ( skiproundrobin[roundrobin] == 0 ) {
                rrUpCheck();
                if ( skiproundrobin[roundrobin] == 0 ) {
                    rrUpCheck();
                }
            }
        }
    } else {
        if ( heldnotes[index].note != -1 ) {
          midi_note(heldnotes[index].channel, heldnotes[index].note, value);
        }
        heldnotes[index].note = -1;
        heldnotes[index].channel = -1;
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
    //kill_channel_notes(0);  // old way before heldnotes
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

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

void DropRock(u8 index, u8 value) {
    particle d = {directional(5, index+10), 0, 0, 0, 5, 0, 0};
    addParticle(d);
}

void DropLight(u8 index, u8 value) {
    particle d = {directional(5, index+10), 63, 63, 63, 5, 0, 0};
    addParticle(d);
}

void DoNote(u8 index, u8 value) {
    if (value > 0) {
        u8 note = grid_params[index].p2 + octave[0] * 12 + keyscale;
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

void DoNoteMarked(u8 index, u8 value) { // like DoNote but for marking any other key with the same note as the one pressed
    if (value > 0) {
        u8 note = grid_params[index].p2 + octave[0] * 12 + keyscale;
        midi_note(grid_params[index].p1, note, value);
        heldnotes[index].note = note;  // heldnotes creates a management system for notes on and off that better handles change
        heldnotes[index].channel = grid_params[index].p1;
        //scan all grid_params[xxx].p2 for those with equal note and color them and this one green
        for ( u8 mdx = 0; mdx < 64; mdx++ ) {
            if ( grid_params[conv64toGrid(mdx)].p2 == grid_params[index].p2 ) {
              hal_plot_led(TYPEPAD, conv64toGrid(mdx), 3, 33, 3); // give temporary color
            }
        }
        hal_plot_led(TYPEPAD, index, 3, 33, 3); // give temporary color
    } else {
        if ( heldnotes[index].note != -1 ) {
          midi_note(heldnotes[index].channel, heldnotes[index].note, value);
        }
        heldnotes[index].note = -1;
        heldnotes[index].channel = -1;
        // uncolor this note and all those with equal note in grid_params[xxx].p2
        for ( u8 mdx = 0; mdx < 64; mdx++ ) {
            u8 gridpad = conv64toGrid(mdx);
            if ( grid_params[gridpad].p2 == grid_params[index].p2 ) {
              // change back to memorized grid color
              hal_plot_led(TYPEPAD, gridpad, grid_colors[gridpad].r, grid_colors[gridpad].g, grid_colors[gridpad].b);
            }
        }
        hal_plot_led(TYPEPAD, index, grid_colors[index].r, grid_colors[index].g, grid_colors[index].b);
    }

}

void FixedNote(u8 index, u8 value) {  // Hard - fixed note that doesn't care about octaves, scales, modes, etc.
    if (value > 0) {
        u8 note = grid_params[index].p2;
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
}

void McpNote(u8 index, u8 value) {
    if (value > 0) {
        u8 note = grid_params[index].p2 + keyscale;
        if ( index < 50 ) {
          note += octave[1] * 12;
          midi_note(mcpSet1, note, value);
        } else {
          note += octave[0] * 12;
          midi_note(mcpSet2, note, value);
        }
        heldnotes[index].note = note;  // heldnotes creates a management system for notes on and off that better handles change
        if ( index < 50 ) {
          heldnotes[index].channel = mcpSet1;
        } else {
          heldnotes[index].channel = mcpSet2;
        }
    } else {
        if ( heldnotes[index].note != -1 ) {
          midi_note(heldnotes[index].channel, heldnotes[index].note, value);
        }
        heldnotes[index].note = -1;
        heldnotes[index].channel = -1;
    }
}

void McpFixedNote(u8 index, u8 value) {  // Like FixedNote but in the Mcp style
    if (value > 0) {
        u8 note = grid_params[index].p2;
        if ( index < 50 ) {
          midi_note(mcpSet1, note, value);
        } else {
          midi_note(mcpSet2, note, value);
        }
        heldnotes[index].note = note;  // heldnotes creates a management system for notes on and off that better handles change
        if ( index < 50 ) {
          heldnotes[index].channel = mcpSet1;
        } else {
          heldnotes[index].channel = mcpSet2;
        }
    } else {
        if ( heldnotes[index].note != -1 ) {
          midi_note(heldnotes[index].channel, heldnotes[index].note, value);
        }
        heldnotes[index].note = -1;
        heldnotes[index].channel = -1;
    }
}

void McpCCStatic(u8 index, u8 value) {
  if (value > 0) {
      u8 cc = grid_params[index].p1;
      u8 val = grid_params[index].p2;
      if ( index > 50 ) {
        midi_cc(mcpSet2, cc, val);
      }
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
    //fixed bug jamming on this:  if changed OPEN drum channels then this needs to sweep for if roundrobin is on a CLOSED channel

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

        DropRock(index, value);

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


void CircuitChromaticSample(u8 index, u8 value) {

    // u8 staggereddrum[4] = {60,62,64,65};
    // u8 patchselect[4] = {8,18,44,50};
    if ( value > 0 ) {
        midi_cc(9, 14, grid_params[index].p2);
        midi_note(9, 60, value);  // the NOTE OFF's are going to be off here. Another reason to need the Held Note Manager!
        heldnotes[index].note = 60;
        heldnotes[index].channel = 9;

        DropLight(index, value);
    } else {
        if ( heldnotes[index].note != -1 ) {
          midi_note(heldnotes[index].channel, heldnotes[index].note, value);
        }
        heldnotes[index].note = -1;
        heldnotes[index].channel = -1;
    }
}

void ChangeOctave(bool isUp, u8 whichOctave) {
    if (isUp) {
      if (octave[whichOctave] + 1 > 10) { return; }
      octave[whichOctave]++;
    } else {
      s8 s8octave = octave[whichOctave];
      if (s8octave - 1 < 0) { return; }
      octave[whichOctave]--;
    }
    color c = {0,0,0};
    switch (octave[whichOctave]) {  // could move to color.c
      case 0:
        c.r = 7;
      break;
      case 1:
        c.r = 7;
        c.b = 10;
      break;
      case 2:
        c.r = 8;
        c.b = 20;
      break;
      case 3:
        c.r = 10;
        c.g = 10;
        c.b = 10;
      break;
      case 4:
        c.g = 10;
      break;
      case 5:
        c.g = 10;
        c.b = 10;
      break;
      case 6:
        c.r = 20;
        c.g = 10;
      break;
      case 7:
        c.r = 40;
      break;
      case 8:
        c.r = 40;
        c.g = 40;
      break;
      case 9:
        c.r = 40;
        c.g = 40;
        c.b = 40;
      break;
      case 10:
        c.r = 40;
        c.b = 63;
        c.g = 50;
      break;
    }
    if ( whichOctave == 0 ) {
      change_color(91, c.r, c.g, c.b);
      change_color(92, c.r, c.g, c.b);
    } else if ( whichOctave == 1) {
      change_color(1, c.r, c.g, c.b);
      change_color(2, c.r, c.g, c.b);
    }
    //(*stateMachine)(EVENT_REDRAW, 0, 0);  // wasteful redraw
    //kill_channel_notes(0);  // old way before heldnotes
}

void ChangeOctaveUp(u8 index, u8 value) {
    if (value > 0 ) {
      (*ChangeOctave)(true, 0);
    }
}

void ChangeOctaveDown(u8 index, u8 value) {
    if (value > 0 ) {
      (*ChangeOctave)(false, 0);
    }
}

void ChangeOctaveUp2(u8 index, u8 value) {
    if (value > 0 ) {
      (*ChangeOctave)(true, 1);
    }
}

void ChangeOctaveDown2(u8 index, u8 value) {
    if (value > 0 ) {
      (*ChangeOctave)(false, 1);
    }
}

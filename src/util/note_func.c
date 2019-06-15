#include "util/note_func.h"
#include "midi/midi.h"
#include "visual/surface.h"
#include "state/state.h"
#include "music/kill.h"

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
        u8 note = grid_params[index].p2 + octave[0] * 12 + memory_store[MEM_KEY];
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

void DoNoteMicrotonal(u8 index, u8 value) {
    if (value > 0) {
        s8 small_octave_adjust = 0; // doing this because the really small count microtonal were not getting low enough
        // it is a compromise because I am not changing the whole octave system over this.
        if (microtonal_count < 11) {
            small_octave_adjust = -1;
        }
        if (microtonal_count < 7) {
            small_octave_adjust = -3;
        }
        if (microtonal_count < 5) {
            small_octave_adjust = -5;
        }
        s8 note = grid_params[index].p2 + (octave[0] + small_octave_adjust) * microtonal_count;
        if (note < 0) { note = 0; }
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
    DropLight(index, value);
}

void DoNoteMarked(u8 index, u8 value) { // like DoNote but for marking any other key with the same note as the one pressed
    if (value > 0) {
        color hitColor = colorRanger(memory_store[MEM_COLOR_SCHEME]* 6, 6);
        u8 note = grid_params[index].p2 + octave[0] * 12 + memory_store[MEM_KEY];
        midi_note(grid_params[index].p1, note, value);
        heldnotes[index].note = note;  // heldnotes creates a management system for notes on and off that better handles change
        heldnotes[index].channel = grid_params[index].p1;
        //scan all grid_params[xxx].p2 for those with equal note and color them and this one green
        for ( u8 mdx = 0; mdx < 64; mdx++ ) {
            if ( grid_params[conv64toGrid(mdx)].p2 == grid_params[index].p2 ) {
              hal_plot_led(TYPEPAD, conv64toGrid(mdx), hitColor.r, hitColor.g, hitColor.b); // give temporary color
            }
        }
        hal_plot_led(TYPEPAD, index, hitColor.r, hitColor.g, hitColor.b); // give temporary color
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
        u8 note = grid_params[index].p2 + memory_store[MEM_KEY];
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
// for expansion: the other CCs are Drum3&4...46....55
// the midi note also changes: I think it is  64 and 65
void CircuitChromaticSample2(u8 index, u8 value) {
    if ( value > 0 ) {
        midi_cc(9, 34, grid_params[index].p2);
        midi_note(9, 62, value);  // the NOTE OFF's are going to be off here. Another reason to need the Held Note Manager!
        heldnotes[index].note = 62;
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

void CircuitMicrotonalSet(u8 index, u8 value) {
    if ( value > 0 ) {
        microtonal_count = grid_params[index].p2;
        for ( u8 cdx = 0; cdx < 32; cdx++) {
            grid_params[conv64toGrid(cdx)].p1 = 0;   
            change_color(conv64toGrid(cdx), 11,11,11 );
        }
        grid_params[index].p1 = 1;
        change_color(index, 44,44,44);
        // then change the number of pads above that allow notes within the microtonal to be on or off
        for ( u8 cdx = 0; cdx < 32; cdx++) {
            bool isOn = true;
            if ( cdx >= microtonal_count ) {
                isOn = false;
            }
            color c = { 11 * isOn, 22 * isOn, 44 * isOn };
            change_color(conv64toGrid(cdx+32), c.r,c.g,c.b);
            if (isOn && microtonal_notes_on[cdx] == 0) {
                change_color(conv64toGrid(cdx+32), 44, 0, 0);
            }
        }
    }
}

void CircuitMicrotonalNotes(u8 index, u8 value) {
    if ( value > 0 ) {
        s8 step = convGridto64(index) - 32;
        if (step < 0) { step = 0;}
        if (step > 31) { step = 31;}
        if (step + 1 <= microtonal_count) {
            if ( step == 0 ) { return; } // disallow shunting of root note. test this theory.
            if (microtonal_notes_on[step] == 0) {
                microtonal_notes_on[step] = 1;
                grid_params[index].p1 = 1;
                change_color(index, 11,22,44);
            } else {
                microtonal_notes_on[step] = 0;
                grid_params[index].p1 = 0;
                change_color(index, 44,0,0);
            }
        }
    }
}
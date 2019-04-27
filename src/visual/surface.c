#include "visual/surface.h"
#include "visual/particle.h"
#include "visual/pressure.h"
#include "music/kill.h"
#include "visual/clear.h"
#include "util/clear_func.h"

// Pad Visual Functions moved to visual/pad.c

color grid_colors[BUTTON_COUNT] = {{0,0,0}};
particle particles[64] = {{0,0,0,0,0,0,0}};
void (*grid_func[BUTTON_COUNT])(u8, u8) = {NULL};
void (*grid_pres[BUTTON_COUNT])(u8, u8) = {NULL};
GridParams grid_params[BUTTON_COUNT] = {{0,0,0,0,0,0,0,0}};
heldnote heldnotes[BUTTON_COUNT] = {{-1,-1,-1,-1}}; // -1 means no note held, otherwise note held
u8 octave[2] = {5,5};
u8 keyscale = 0;
u8 modal = 8;
u8 scaleOffset = 0;
u8 hideNonscale = 0;
u8 velocityCurve = 0;
u8 selectedSlot = 0;
u8 mcpSet1 = 0;
u8 mcpSet2 = 0;

void exit_surface() {
  kill_channel_notes(0);
  clear_leds();
  clear_all_functions();
}

void change_color(u8 index, u8 r, u8 g, u8 b) {
  grid_colors[index].r = r;
  grid_colors[index].g = g;
  grid_colors[index].b = b;
  hal_plot_led(TYPEPAD, index, grid_colors[index].r, grid_colors[index].g, grid_colors[index].b);
}

void red_notes() {
    // see if notes are outside the range of valid midi notes (based on octave) and draw red if < 0 or > 127
    for ( u8 cdx = 1; cdx < 9; cdx++ ) {
        for ( u8 rdx = 1; rdx < 9; rdx++ ) {
            u8 note =  grid_params[rdx*10+cdx].p2 + octave[0] * 12 + keyscale;
            if (note < 0 || note > 127) {
                change_color(rdx*10+cdx, 50, 0, 0);
                grid_func[rdx*10+cdx] = &NullFunction;  // have to see if this will go back once octave range is good again.
            }
        }
    }
}

void redraw_surface() {  // this repaints all pads but doesn't change functions, etc.
  for (u8 edx = 0; edx < BUTTON_COUNT; edx++) {
      hal_plot_led(TYPEPAD, edx, grid_colors[edx].r, grid_colors[edx].g, grid_colors[edx].b );
  }
}

void prep_surface () {  // this will be broken down and smartened up :)
    for (int i=0; i < 10; ++i) {
        for (int j=0; j < 10; ++j) {
            color clr = {j*2, i*2, i+j};
            grid_colors[j*10 + i] = clr;
            grid_func[j*10 + i] = &FilledDoMore;
            grid_pres[j*10 + i] = &NullFunction;
            hal_plot_led(TYPEPAD, j*10 + i, clr.r, clr.g, clr.b );
        }
    }
    grid_func[44] = &FilledDoStar;
    grid_func[45] = &FilledDoStar;
    grid_func[54] = &FilledDoStar;
    grid_func[55] = &FilledDoStar;
    grid_func[66] = &FilledDoSpiral;
    grid_func[36] = &FilledDoSpiral;
    grid_func[33] = &FilledDoSpiral;
    grid_func[63] = &FilledDoSpiral;
    grid_func[43] = &FilledDoNoteBeams;
    grid_func[53] = &FilledDoNoteBeams;
    grid_func[64] = &FilledDoNoteBeams;
    grid_func[65] = &FilledDoNoteBeams;
    grid_func[34] = &FilledDoNoteBeams;
    grid_func[35] = &FilledDoNoteBeams;
    grid_func[56] = &FilledDoNoteBeams;
    grid_func[46] = &FilledDoNoteBeams;
    grid_func[11] = &FilledDoSpiral;
    grid_func[81] = &FilledDoSpiral;
    grid_func[88] = &FilledDoSpiral;
    grid_func[18] = &FilledDoSpiral;
    grid_func[19] = &FilledDoLeft;
    grid_func[29] = &FilledDoLeft;
    grid_func[39] = &FilledDoLeft;
    grid_func[49] = &FilledDoLeft;
    grid_func[59] = &FilledDoLeft;
    grid_func[69] = &FilledDoLeft;
    grid_func[79] = &FilledDoLeft;
    grid_func[89] = &FilledDoLeft;
    grid_func[12] = &FilledDoNoteTest;
    grid_func[22] = &FilledDoNoteTest;
    grid_func[32] = &FilledDoNoteTest;
    grid_func[42] = &FilledDoNoteTest;
    grid_func[72] = &NullFunction;
    grid_func[27] = &NullFunction;
    grid_func[61] = &NullFunction;
    grid_func[26] = &NullFunction;
    grid_pres[72] = &FilledPressure;
    grid_pres[27] = &FilledPressure;
    grid_pres[61] = &FilledPressure;
    grid_pres[26] = &Burn;
}

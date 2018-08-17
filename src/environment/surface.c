#include "environment/surface.h"
#include "atoms/visual/particle.h"
#include "atoms/visual/pressure.h"
#include "molecules/music/kill.h"
#include "molecules/visual/clear.h"
#include "atoms/function/clear_func.h"

// Pad Visual Functions moved to molecules/visual/pad.c

color grid_colors[BUTTON_COUNT] = {{0,0,0}};
particle particles[64] = {{0,0,0,0,0,0,0}};
void (*grid_func[BUTTON_COUNT])(u8, u8) = {NULL};
void (*grid_pres[BUTTON_COUNT])(u8, u8) = {NULL};
GridParams grid_params[BUTTON_COUNT] = {{0,0,0,0,0,0}};

void exit_surface() {
  kill_channel_notes(0);
  clear_leds();
  clear_all_functions();
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

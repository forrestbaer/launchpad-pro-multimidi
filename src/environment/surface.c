#include "environment/surface.h"
#include "molecules/visual/pad.h"
#include "environment/timer.h"
#include "atoms/visual/particle.h"
#include "atoms/visual/pressure.h"
#include "atoms/midi/midi.h"

color grid_colors[BUTTON_COUNT] = {{0,0,0}};
particle particles[64] = {{0,0,0,0,0,0,0}};
void (*grid_func[BUTTON_COUNT])(u8, u8) = {NULL};
void (*grid_pres[BUTTON_COUNT])(u8, u8) = {NULL};

// PLEASE NOTE: All of this is here TEMP to Test out the Complex Array of Functional Pointers. It will be broken into better
// Categories next!

void recrsvDirFill(u8 dirInt, u8 index, u8 recrsvDepth) { //recursive Directional Line Paint
  u8 rtnPad = directional(dirInt, index); // basically go 1 of 8 directions and fill in color that way until hit the edge
  if (rtnPad != 0) {
    u8 variance = animCnt + 20 * recrsvDepth;
    if (variance > 95 ) {
      variance -= 95;
    }
    color clr = colorRanger(animCnt+variance, 2);
    hal_plot_led(TYPEPAD, rtnPad, clr.r, clr.g, clr.b );
    recrsvDirFill(dirInt, rtnPad, recrsvDepth + 1);
  }
}

void DoMore(u8 setting, u8 index, u8 value) {
    if ( value > 0 ) {
      hal_plot_led(TYPEPAD, index, value / 2, value / 2, value / 2);
      for ( u8 cdx=0; cdx < DIR_NUM; cdx++ ) {
        u8 rtnPad = directional(cdx, index);
        if (rtnPad != 0) {
            color clr = color8(cdx, 0);
            hal_plot_led(TYPEPAD, rtnPad, clr.r * value / 63, clr.g * value / 63, clr.b * value / 63 );
            u8 rtnPad2 = directional(cdx, rtnPad);
            if (rtnPad2 != 0) {
                hal_plot_led(TYPEPAD, rtnPad2, clr.r * value / 63, clr.g * value / 63, clr.b * value / 63 );
            }
        }
      }
    } else {
      hal_plot_led(TYPEPAD, index, grid_colors[index].r, grid_colors[index].g, grid_colors[index].b );
      for ( u8 cdx=0; cdx < DIR_NUM; cdx++ ) {
        u8 rtnPad = directional(cdx, index);
        if (rtnPad != 0) {
            hal_plot_led(TYPEPAD, rtnPad, grid_colors[rtnPad].r, grid_colors[rtnPad].g, grid_colors[rtnPad].b  );
            u8 rtnPad2 = directional(cdx, rtnPad);
            if (rtnPad2 != 0) {
                hal_plot_led(TYPEPAD, rtnPad2, grid_colors[rtnPad2].r, grid_colors[rtnPad2].g, grid_colors[rtnPad2].b  );
            }
        }
      }
    }
}

void FilledDoMore(u8 index, u8 value) {  // This is to demo that a broad function "DoMore" can be set up but the Array holds Functions with more defined behavior for each Array item to create a grid of varying but similar functionality
    (*DoMore)(69, index, value);
}

void DoLess(u8 setting, u8 index, u8 value) {
    if (value > 0 ) {
      for ( u8 idx = 0; idx < 8; idx++) {
        color clr = color8(idx, 0);
        particle p = {directional(idx, index), clr.r * value / 63, clr.g * value / 63, clr.b * value / 63, idx, 1, 0};
        addParticle(p);
      }
    }
}

void FilledDoLess(u8 index, u8 value) {
    (*DoLess)(23, index, value);
}

void DoLeft(u8 setting, u8 index, u8 value) {
    if (value > 0 ) {
        particle p = {directional(7, index), 22, 0, 44, 7, 0, 0};
        addParticle(p);
    }
}

void FilledDoLeft(u8 index, u8 value) {
    (*DoLeft)(23, index, value);
}

void DoNote(u8 setting, u8 index, u8 value) {
    midi_note(0 | setting, index, value);
    if (value > 0 ) {
        particle p = {directional(3, index), 44, 44, 44, 3, 2, 0};
        addParticle(p);
    }
}

void FilledDoNote(u8 index, u8 value) {
    (*DoNote)(0, index, value);
}


void Pressure(u8 setting, u8 index, u8 value) {
  if ( value > 64 ) {
      for ( u8 cdx=0; cdx < DIR_NUM; cdx++ ) {
          u8 rtnPad = directional(cdx, index);
          if (rtnPad != 0) {
              hal_plot_led(TYPEPAD, rtnPad, (value - 64), 0, 0 );
          }
      }
  }
  if ( value <= 64 ) {
    for ( u8 cdx=0; cdx < DIR_NUM; cdx++ ) {
        u8 rtnPad = directional(cdx, index);
        if (rtnPad != 0) {
            hal_plot_led(TYPEPAD, rtnPad, grid_colors[rtnPad].r, grid_colors[rtnPad].g, grid_colors[rtnPad].b );
        }
    }
  }
}

void FilledPressure(u8 index, u8 value) {
    (*Pressure)(23, index, value);
}

void NullFunction(u8 index, u8 value) {
    return; //Do nothing! But receives parameters to avoid error.
}

void prep_surface () {
    for (int i=0; i < 10; ++i) {
        for (int j=0; j < 10; ++j) {
            color clr = {j*2, i*2, i+j};
            grid_colors[j*10 + i] = clr;
            grid_func[j*10 + i] = &FilledDoMore;
            grid_pres[j*10 + i] = &NullFunction;
            hal_plot_led(TYPEPAD, j*10 + i, clr.r, clr.g, clr.b );
        }
    }
    grid_func[44] = &FilledDoLess;
    grid_func[55] = &FilledDoLess;
    grid_func[66] = &FilledDoLess;
    grid_func[11] = &FilledDoLess;
    grid_func[19] = &FilledDoLeft;
    grid_func[29] = &FilledDoLeft;
    grid_func[39] = &FilledDoLeft;
    grid_func[49] = &FilledDoLeft;
    grid_func[59] = &FilledDoLeft;
    grid_func[69] = &FilledDoLeft;
    grid_func[79] = &FilledDoLeft;
    grid_func[89] = &FilledDoLeft;
    grid_func[12] = &FilledDoNote;
    grid_func[22] = &FilledDoNote;
    grid_func[32] = &FilledDoNote;
    grid_func[42] = &FilledDoNote;
    grid_func[72] = &NullFunction;
    grid_func[27] = &NullFunction;
    grid_func[61] = &NullFunction;
    grid_func[34] = &NullFunction;

    grid_pres[72] = &FilledPressure;
    grid_pres[27] = &FilledPressure;
    grid_pres[61] = &FilledPressure;
    grid_pres[34] = &Burn;
}

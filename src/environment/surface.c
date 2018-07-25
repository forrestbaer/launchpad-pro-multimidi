#include "environment/surface.h"
#include "molecules/visual/pad.h"
#include "environment/timer.h"

color grid_colors[BUTTON_COUNT] = {{0,0,0}};

void (*grid_func[BUTTON_COUNT])(u8, u8) = {NULL};

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
    if ( value > 0 ) {
      hal_plot_led(TYPEPAD, index, 0, value / 4, value / 2 );

      recrsvDirFill(DIR_UP, index, 0);

      // u8 rtnPad = directional(DIR_UP, index);
      // if (rtnPad != 0) {  // duh, make recursive function!
      //   color clr = colorRanger(animCnt, 2);
      //   hal_plot_led(TYPEPAD, rtnPad, clr.r, clr.g, clr.b );
      //   u8 rtnPad2 = directional(DIR_UP, rtnPad);
      //   if (rtnPad2 != 0) {
      //     clr = colorRanger(animCnt+20, 2);
      //     hal_plot_led(TYPEPAD, rtnPad2, clr.r, clr.g, clr.b );
      //     u8 rtnPad3 = directional(DIR_UP, rtnPad2);
      //     if (rtnPad3 != 0) {
      //       clr = colorRanger(animCnt+40, 2);
      //       hal_plot_led(TYPEPAD, rtnPad3, clr.r, clr.g, clr.b );
      //     }
      //   }
      // }

    } else {
      hal_plot_led(TYPEPAD, index, grid_colors[index].r, grid_colors[index].g, grid_colors[index].b );
      // this doesn't clear the left over Paint Up stuff
    }
}

void FilledDoLess(u8 index, u8 value) {
    (*DoLess)(23, index, value);
}

void prep_surface () {
  for (int i=0; i < 10; ++i) {
      for (int j=0; j < 10; ++j) {
          color clr = {j*2, i*2, i+j};
          grid_colors[j*10 + i] = clr;
          grid_func[j*10 + i] = &FilledDoMore;
      }
  }
  grid_func[44] = &FilledDoLess;
  grid_func[55] = &FilledDoLess;
  grid_func[66] = &FilledDoLess;
  grid_func[11] = &FilledDoLess;
}

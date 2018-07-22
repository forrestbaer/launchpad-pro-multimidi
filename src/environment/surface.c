#include "environment/surface.h"

color grid_colors[BUTTON_COUNT] = {{0,0,0}};

void (*grid_func[BUTTON_COUNT])(u8, u8) = {NULL};

void DoMore(u8 setting, u8 index, u8 value) {
    if ( value > 0 ) {
      hal_plot_led(TYPEPAD, index, value / 2, 0, 0 );
    } else {
      hal_plot_led(TYPEPAD, index, grid_colors[index].r, grid_colors[index].g, grid_colors[index].b );
    }
}

void FilledDoMore(u8 index, u8 value) {
    (*DoMore)(69, index, value);
}

void DoLess(u8 setting, u8 index, u8 value) {
    if ( value > 0 ) {
      hal_plot_led(TYPEPAD, index, 0, value / 4, value / 2 );
    } else {
      hal_plot_led(TYPEPAD, index, grid_colors[index].r, grid_colors[index].g, grid_colors[index].b );
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
}

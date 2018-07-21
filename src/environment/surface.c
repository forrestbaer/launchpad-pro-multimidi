#include "environment/surface.h"

color grid_colors[BUTTON_COUNT] = {{0,0,0}};

void prep_surface () {
  for (int i=0; i < 10; ++i) {
      for (int j=0; j < 10; ++j) {
          color clr = {j*2, i*2, i+j};
          grid_colors[j*10 + i] = clr;
      }
  }
}

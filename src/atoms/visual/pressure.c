#include "atoms/visual/pressure.h"
#include "environment/surface.h"
#include "molecules/visual/pad.h"
#include "atoms/visual/particle.h"
#include "molecules/visual/pad.h"

void thresholdTool(u8 threshold, u8 dir, u8 index, u8 value, u8 r, u8 g, u8 b) {
    u8 rtnPad = 0;  //an arduous "manual" pressure based "animation"
    if ( value > threshold ) {
      rtnPad = directional(dir, index);
      if (rtnPad != 0) {
          hal_plot_led(TYPEPAD, rtnPad, r, g, b );
      }
    } else {
      rtnPad = directional(dir, index);
      hal_plot_led(TYPEPAD, rtnPad, grid_colors[rtnPad].r, grid_colors[rtnPad].g, grid_colors[rtnPad].b );
    }
}
void thresholdTool2(u8 threshold, u8 dir, u8 index, u8 value, u8 r, u8 g, u8 b) {
    u8 rtnPad = 0;  //an arduous "manual" pressure based "animation"
    if ( value > threshold ) {
      rtnPad = directional(dir, index);
      rtnPad = directional(dir, rtnPad);
      if (rtnPad != 0) {
          hal_plot_led(TYPEPAD, rtnPad, r, g, b );
      }
    } else {
      rtnPad = directional(dir, index);
      rtnPad = directional(dir, rtnPad);
      hal_plot_led(TYPEPAD, rtnPad, grid_colors[rtnPad].r, grid_colors[rtnPad].g, grid_colors[rtnPad].b );
    }
}

void Burn(u8 index, u8 value) {
    thresholdTool(30, 5, index, value, 12, 0, 0);
    thresholdTool(35, 6, index, value, 31, 0, 0);
    thresholdTool(41, 7, index, value, 31, 11, 0);
    thresholdTool(47, 0, index, value, 41, 11, 0);
    thresholdTool(52, 1, index, value, 51, 17, 0);
    thresholdTool(57, 2, index, value, 61, 21, 0);
    thresholdTool(62, 3, index, value, 60, 31, 0);
    thresholdTool(68, 4, index, value, 57, 41, 0);
    thresholdTool2(73, 5, index, value, 47, 51, 0);
    thresholdTool2(79, 6, index, value, 44, 61, 0);
    thresholdTool2(83, 7, index, value, 34, 61, 0);
    thresholdTool2(87, 0, index, value, 24, 61, 0);
    thresholdTool2(94, 1, index, value, 4, 61, 0);
    thresholdTool2(100, 2, index, value, 20, 61, 20);
    thresholdTool2(110, 3, index, value, 44, 61, 40);
    thresholdTool2(120, 4, index, value, 63, 61, 60);
}

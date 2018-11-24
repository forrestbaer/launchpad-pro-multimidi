#include "atoms/function/cc_func.h"
#include "atoms/midi/midi.h"
#include "environment/surface.h"
#include "environment/state.h"

void SliderHit(u8 index, u8 value) {
    if (value > 0 ) {
      // not sure if this does anything
    }
}
void SliderPressure(u8 index, u8 value) {
    // this might not work! :)  ...but it does! Awesome!
    grid_params[index].p5 = grid_params[index].p7; // put last p7 value in p5... ??? Might want to have some logic for IF NO Change ?? Skip this whole bit???
    // only worries are "interupts" or the flow of multiple pressure pad events getting inputted in the right order, seems to be working
    // tricky stuff ahead!
    grid_params[index].p7 = value;

    // check the whole column for other action and the current one too.

    // if no other pads in delta then its a straight hard value (unless ??? others already fell off)
    // probably need the buffer system in effect...
    // this is happening pretty instantianiously so may check too fast for actual human interaction

    u8 column = index % 10;

    u8 otherActives = 0;
    for ( u8 cdx = 1; cdx < 9; cdx++ ) { // check the column for other interactivity.
        if ( grid_params[cdx*10+column].p7 != 0 && grid_params[cdx*10+column].p5 != 0 && index != cdx*10+column ) { // simplest case...
            otherActives++;
        }
        hal_plot_led(TYPEPAD, cdx*10+column, grid_colors[cdx*10+column].r / 4, grid_colors[cdx*10+column].g / 4, grid_colors[cdx*10+column].b / 4); // give temporary color
    }
    if ( otherActives == 0 ) {
        // nothing else happening....
        u8 cntDirty = 0;
        // cntDirty is about: If got in state of otherActives > 0 then shouldn't allow back into here until all in column have gone back to 0 pressure. :)
        for ( u8 cdx = 1; cdx < 9; cdx++ ) {
          if (grid_params[cdx*10+column].p6 != 0) {
            cntDirty++;
          }
        }
        if ( cntDirty == 0 ) {
          midi_cc(column-1, grid_params[index].p3, grid_params[index].p2);
          hal_plot_led(TYPEPAD, index, grid_colors[index].r, grid_colors[index].g, grid_colors[index].b); // give defined color back to hit one
        }
        // so send the 'hard value' to slider.
    } else if ( otherActives == 1 ) {
        grid_params[index].p6 = 1;
        for ( u8 cdx = 1; cdx < 9; cdx++ ) { // check the column for other interactivity.
            if ( grid_params[cdx*10+column].p7 != 0 && grid_params[cdx*10+column].p5 != 0 && grid_params[index].p7 != 0 && grid_params[index].p5 != 0 && index != cdx*10+column ) { // its active, update trying checking both current and other
                if ( (grid_params[cdx*10+column].p7 >= grid_params[cdx*10+column].p5) ||
                      (grid_params[index].p7 >= grid_params[index].p5) ) {
                    // get a pressure ratio
                    u8 ratioX100 = ((grid_params[index].p7 * 127 / 127) * 127) / (grid_params[cdx*10+column].p5 * 127 / 127); // ?? .p5 on other ?? not sure of this
                    if (ratioX100 > 127) { ratioX100 = 127; } // workaround until math fixed
                    // midi_cc(10, ratioX100, 0);  //TEST!!!
                    // midi_cc(14, grid_params[index].p7, grid_params[index].p5);
                    // midi_cc(15, grid_params[index].p2, grid_params[cdx*10+column].p2);  // TEST!!!!
                    // get the 2 pads associated hard value
                    u8 diff = 0;
                    u8 bottom = 0;
                    if ( grid_params[index].p2 > grid_params[cdx*10+column].p2 ) {
                      diff = grid_params[index].p2 - grid_params[cdx*10+column].p2;
                      bottom = grid_params[cdx*10+column].p2;
                    } else {
                      diff = grid_params[cdx*10+column].p2 - grid_params[index].p2;
                      bottom = grid_params[index].p2;
                    }
                    u8 weightedAvg = bottom + diff * ratioX100 / 127;
                    // send CC message with the blended hard value
                    midi_cc(grid_params[index].p1, grid_params[index].p3, weightedAvg);
                    hal_plot_led(TYPEPAD, index, grid_colors[index].r/2, grid_colors[index].g/2, grid_colors[index].b/2);
                    hal_plot_led(TYPEPAD, cdx*10+column, grid_colors[cdx*10+column].r/2, grid_colors[cdx*10+column].g/2, grid_colors[cdx*10+column].b/2);
                }  // else means both are falling and we don't want to send CC message if this case.
            }
        }
    } else if ( otherActives >= 2 ) {
        // hypothetically could work holding 3 pads but I don't want to solve that now.

    }

    if ( value == 0 ) {  //once you hit 0 clear out the p5 (last value)  ??? Double check that!
      grid_params[index].p5 = 0;
      grid_params[index].p6 = 0;
    }
}

#include "environment/state.h"
//#include "molecules/music/kill.h"
//#include "molecules/visual/clear.h"
#include "environment/surface.h"
#include "molecules/time/animation.h"
#include "atoms/visual/color.h"
//#include "atoms/function/clear_func.h"
//#include "atoms/function/mode_func.h"

LpState current_state = LP_PLAY_MODE;

u8 tempCount = 0;

// new idea for some states: play state vs build state... can build custom playing surface then play it.

void state_play(StateEvent msg, u8 index, u8 value) {
  if (msg == EVENT_EXIT) {
    exit_surface();
    return;
  }
  if (msg == EVENT_ENTER) {
    current_state = LP_PLAY_MODE; // for side queries of state...timer?
    prep_surface();
    return;
  }
  if (msg == EVENT_INPUT) {
    (*grid_func[index])(index, value);
    return;
  }
  if (msg == EVENT_PRESSURE) {  // this is cool, moving this to state too, then aftertouch only happens when in right state
    hal_send_midi(USBMIDI, POLYAFTERTOUCH | 0, index, value);
    (*grid_pres[index])(index, value);
    return;
  }
  if (msg == EVENT_CLOCK) {
    tempCount++;
    if (tempCount > 127) { tempCount = 0; }
    color clr = colorRanger( tempCount, 2 );
    hal_plot_led(TYPEPAD, 88, clr.r, clr.g, clr.b);
    color clr2 = colorRanger( ledloop(tempCount), 1 );
    hal_plot_led(TYPEPAD, 18, clr2.r, clr2.g, clr2.b);
    color clr3 = colorRanger( ledloop(tempCount), 0 );
    hal_plot_led(TYPEPAD, 81, clr3.r, clr3.g, clr3.b);
    color clr4 = colorRanger( ledloop(tempCount), 3 );
    hal_plot_led(TYPEPAD, 11, clr4.r, clr4.g, clr4.b);

    //didn't get this to work yet...whatevez 4 now.
    // grid_colors[91] = colorRotator(grid_colors[91], 1);
    // hal_plot_led(TYPEPAD, 91, grid_colors[91].r, grid_colors[91].g, grid_colors[91].b);
    return;
  }
}

void state_off(StateEvent msg, u8 index, u8 value) {
  if (msg == EVENT_EXIT) {
    exit_surface();
    return;
  }
  if (msg == EVENT_ENTER) {
    current_state = LP_OFF_MODE; // for side queries of state...?
    return;
  }
  if (msg == EVENT_INPUT) {
    //transition_state( state_play );
    return;
  }
  if (msg == EVENT_CLOCK) {
    tempCount++;
    if (tempCount > 127) { tempCount = 0; }
    for (u8 fdx = 0; fdx < 100; fdx++) {  // this should rainbow animate the whole screen in a rough layout.
        u8 tempModCount = tempCount + fdx;
        if ( tempModCount > 127 ) { tempModCount -= 127; }
        color clr = colorRanger( tempModCount, 2 );
        hal_plot_led(TYPEPAD, fdx, clr.r, clr.g, clr.b);
    }
    return;
  }
}

void state_overlay(StateEvent msg, u8 index, u8 value) {
  if (msg == EVENT_CLOCK) {
    tempCount++;
    if (tempCount > 63)  {
        tempCount = 0;
        transition_state ( state_off );
        return;
    }
    for (int i=0; i < 10; ++i) {
        for (int j=0; j < 10; ++j) {
            color clr = grid_colors[j*10 + i];
            if (clr.g > 0) { clr.g--; }
            if (clr.r > 0) { clr.r--; }
            if (clr.b > 0) { clr.b--; }
            // grid_colors[j*10 + i] = clr;
            // hal_plot_led(TYPEPAD, j*10 + i, clr.r, clr.g, clr.b );
            change_color(j*10 + i, clr.r, clr.g, clr.b);
        }
    }
    return;
  }
}

void state_transit(StateEvent msg, u8 index, u8 value) {
  if (msg == EVENT_EXIT) {
    return;
  }
  if (msg == EVENT_ENTER) {
    //current_state = LP_OFF_MODE; // for side queries of state...timer?
    //hal_plot_led(TYPEPAD, 13, 33, 0, 44);
    tempCount = 0;
    return;
  }
  if (msg == EVENT_CLOCK) {
    tempCount++;
    if (tempCount > 63)  {
        tempCount = 0;
        transition_state ( state_overlay );
        return;
    }
    for (int i=0; i < 10; ++i) {
        for (int j=0; j < 10; ++j) {
            color clr = grid_colors[j*10 + i];
            clr.g += 1;
            if (clr.g > 63) { clr.g = 63; }
            // grid_colors[j*10 + i] = clr;
            // hal_plot_led(TYPEPAD, j*10 + i, clr.r, clr.g, clr.b );
            change_color(j*10 + i, clr.r, clr.g, clr.b);
        }
    }
    return;
  }
}

void (*stateMachine)(StateEvent msg, u8 index, u8 value) = state_play;

void transition_state( void (*funcIn)(StateEvent, u8, u8) ) {
    // ON EXIT.... a real state machine, event driven.
    (*stateMachine)(EVENT_EXIT, 0, 0);

    //transition
    stateMachine = (*funcIn);

    // used to do this...   // draw_session_mode(); or draw_note_mode() etc.
    // ON ENTER
    (*stateMachine)(EVENT_ENTER, 0, 0);  // run the passed in Function and give it a state.  May not need to pass in state now.
}

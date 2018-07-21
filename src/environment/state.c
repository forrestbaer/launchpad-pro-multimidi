#include "environment/state.h"
#include "molecules/music/kill.h"
#include "molecules/visual/clear.h"
#include "environment/surface.h"
#include "molecules/time/animation.h"

LpState current_state = LP_PLAY_MODE;

u8 tempCount = 0;

void state_play(StateEvent msg) {
  if (msg == EVENT_EXIT) {
    // this function is going to live on a different level, but the types of things it would do are...
    // kill_channel_notes(0);
    // clear_leds();
    hal_plot_led(TYPEPAD, 12, 44, 0, 0);
    return;
  }
  if (msg == EVENT_ENTER) {
    current_state = LP_PLAY_MODE; // for side queries of state...timer?
    hal_plot_led(TYPEPAD, 11, 0, 0, 44);
    for (int i=0; i < 10; ++i) {
        for (int j=0; j < 10; ++j) {
            color clr = grid_colors[j*10 + i];
            hal_plot_led(TYPEPAD, j*10 + i, clr.r, clr.g, clr.b);
        }
    }
    return;
  }
  if (msg == EVENT_CLOCK) {
    tempCount++;
    if (tempCount > 60) { tempCount = 0; }
    hal_plot_led(TYPEPAD, 88, tempCount, 0, tempCount);
    return;
  }
}

void state_off(StateEvent msg) {
  if (msg == EVENT_EXIT) {
    // this function is going to live on a different level, but the types of things it would do are...
    // kill_channel_notes(0);
    // clear_leds();
    hal_plot_led(TYPEPAD, 14, 0, 33, 0);
    return;
  }
  if (msg == EVENT_ENTER) {
    current_state = LP_OFF_MODE; // for side queries of state...?
    hal_plot_led(TYPEPAD, 13, 33, 0, 44);
    return;
  }
  if (msg == EVENT_CLOCK) {
    tempCount++;
    if (tempCount > 127)  { tempCount = 0; }
    hal_plot_led(TYPEPAD, 88, ledloop(tempCount), 0, ledloop(tempCount));
    return;
  }
}

void state_overlay(StateEvent msg) {
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
            grid_colors[j*10 + i] = clr;
            hal_plot_led(TYPEPAD, j*10 + i, clr.r, clr.g, clr.b );
        }
    }
    return;
  }
}

void state_transit(StateEvent msg) {
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
            grid_colors[j*10 + i] = clr;
            hal_plot_led(TYPEPAD, j*10 + i, clr.r, clr.g, clr.b );
        }
    }
    return;
  }
}

void (*stateMachine)(StateEvent msg) = state_play;

void transition_state( void (*funcIn)(StateEvent) ) {
    // ON EXIT.... a real state machine, event driven.
    (*stateMachine)(EVENT_EXIT);

    //transition
    stateMachine = (*funcIn);

    // used to do this...   // draw_session_mode(); or draw_note_mode() etc.
    // ON ENTER
    (*stateMachine)(EVENT_ENTER);  // run the passed in Function and give it a state.  May not need to pass in state now.
}

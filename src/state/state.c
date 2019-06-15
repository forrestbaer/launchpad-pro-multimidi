#include "state/state.h"
#include "visual/surface.h"
#include "time/animation.h"
#include "visual/color.h"
#include "state/states/setup.h"
#include "state/states/scalearp.h"
#include "state/states/mastercontrol.h"
#include "state/states/circuitpad.h"
#include "state/states/keyscale.h"
#include "state/states/digitonepad.h"

LpState current_state = LP_PLAY_STATE;

u8 tempCount = 0;

// new idea for some states: play state vs build state... can build custom playing surface then play it.

// some sample State Machines (other more Real ones are in src/state/states/...)
void state_play(StateEvent msg, u8 index, u8 value) {
  if (msg == EVENT_EXIT) {
    exit_surface();
    return;
  }
  if (msg == EVENT_ENTER) {
    current_state = LP_PLAY_STATE; // for side queries of state...timer?
    memory_store[MEM_LAST_STATE] = LP_PLAY_STATE;
    hal_write_flash(0, memory_store, 30);
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
    current_state = LP_OFF_STATE; // for side queries of state...?
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
    //current_state = LP_OFF_STATE; // for side queries of state...timer?
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

    // ON ENTER
    (*stateMachine)(EVENT_ENTER, 0, 0);  // run the passed in Function and give it a state.  May not need to pass in state now.
}

// main switch function to Transition state
void StateFunc(LpState setting, u8 index, u8 value) {
    switch (setting) {
        case LP_PLAY_STATE:
            transition_state ( state_play );
        break;
        case LP_OFF_STATE:
            transition_state ( state_off );
        break;
        case LP_OVERLAY_STATE:
            transition_state ( state_overlay );
        break;
        case LP_SETUP_STATE:
            transition_state ( state_setup );
        break;
        case LP_SCALEARP_STATE:
            transition_state ( state_scalearp );
        break;
        case LP_MASTERCONTROL_STATE:
            transition_state ( state_mastercontrol );
        break;
        case LP_CIRCUITPAD_STATE:
            transition_state ( state_circuitpad );
        break;
        case LP_KEYSCALE_STATE:
            transition_state ( state_keyscale );
        break;
        case LP_DIGITONEPAD_STATE:
            transition_state ( state_digitonepad );
        break;
        case LP_NUM_STATES:
        break;
    }
}

// state external pointer functions:
void StatePlay(u8 index, u8 value) {
    (*StateFunc)(LP_PLAY_STATE, index, value);
}

void StateOff(u8 index, u8 value) {
    (*StateFunc)(LP_OFF_STATE, index, value);
}

void StateScaleArp(u8 index, u8 value) {
    (*StateFunc)(LP_SCALEARP_STATE, index, value);
}

void StateMastercontrol(u8 index, u8 value) {
    (*StateFunc)(LP_MASTERCONTROL_STATE, index, value);
}

void StateCircuitpad(u8 index, u8 value) {
    (*StateFunc)(LP_CIRCUITPAD_STATE, index, value);
}

void StateKeyscale(u8 index, u8 value) {
    (*StateFunc)(LP_KEYSCALE_STATE, index, value);
}

void StateDigitonepad(u8 index, u8 value) {
    (*StateFunc)(LP_DIGITONEPAD_STATE, index, value);
}
#include "organisms/states/digitonepad.h"
#include "environment/surface.h"
#include "organisms/visual/columnset.h"
#include "organisms/visual/rowset.h"
#include "atoms/function/clear_func.h"
#include "molecules/visual/clear.h"

u8 digitone_state = 0;

void ToggleDigitoneState(u8 index, u8 value) {
      if (value > 0) {
          digitone_state++;
          clear_all_functions();
          clear_leds();
          if ( digitone_state > 4 ) {
              digitone_state = 0;
          }
          switch(digitone_state) {
            case 0:
              build_digitonepad();
            break;
            case 1:
              build_digitone_delay();
            break;
            case 2:
              build_digitone_chorus();
            break;
            case 3:
              build_digitone_reverb();
            break;
            case 4:
              build_digitone_lfo();
            break;
          }
      }
}

/* Notes on the Double-CC FX Controls and others:

  Volume 7 is the Coarse Control ranges from 0 to 127
  and    39 is the fine control and goes from 0 to 127 per each Coarse (this is standard)

  Delay time (standard) 15 and 47
    PingPong on/off is 16 (OFF = 0 and ON = 1) 48 is always 0
    Stereo Width (standard) 17 and 49
    Feedback (standard) 18 and 50
    Feedback HPF is only 72 
    Feedback LPF is only 73
    Reverb Send (standard) is 19 and 51
    Mix Volume CC 13 !!!! Actual !! Manual is wrong!!

  Reverb, no surprises

    Predelay 21 53
    Decay Time 74
    Shelving Freq 75
    Shelving Gain 22 54
    Highpass Filter 76
    Lowpass Filter 77
    Mix Volume 14 !!! Actual!! Manual is wrong!

  Chorus no surprises

    Depth 3 35
    Speed 9 41
    High-pass 70
    Width 71
    Delay Send 12 44
    Reverb Send 13 45
    Mix Volume 12 !!!! Manual is wrong!!!

  LFO1
    Multiplier: 108 only. Values ranging from 0 (BPM x1) thru 11 (BPM 2k) then 12 (x1 non-BPM) thru 23 (x2k non-BPM)
    FadeIn/FadeOut: 109 only. 0 = -64 , 64 = 0 (neutral), 127 = 63  (99 = linear fade out, 31 = linear fade in)
    Start Phase: 112 only. just 0 to 127 range
    Mode: 113 only. Values 0 thru 4. 0 Free, 1 Triggered, 2 Hold, 3 One-shot, 4 Half
    Destination: 110 only. Value 0 is none, then jumps to 17 to 69 (odd!) skips a few
    Wave: 111 only. Values 0 thru 6, 0 tri, 1 Sin, 2 Sqr, 3 Saw, 4 Exp, 5 Ramp, 6 Random
    Speed: 28 and 60. Value 0 and 0 = -64.00 ---- Value 64 and 0 = 0 point ---- Value 127 and 127 = 63.99
    Depth: 29 and 61. Value 0 and 0 = -128.00 ---- Value 64 and 0 = 0 point ---- Value 127 and 127 = 127.98
  LFO2 same as 1 functions
    Destination: 116 only. Different than LFO 1 because 1 thru 8 are LFO2 modulating LFO 1, then similar to LFO 1

  Synth
    Algorithm CC 90. Values 0 thru 7 = algo 1 thru 8
    C Ratio CC 91. Values 0 thru 18. 0 = 0.25, 3 = 1.0, 6 = 4.0, 18 = 16.0
    A Ratio CC 92. (NOT AS Above!) Values 0 thru 35.  More steps between 0.25 and 16.0
    B Ratio. CC 16 and 48. 0,0 = 0.25,0.25. CC48 goes up first and when it reaches 127 then goes to 1,0.
       Highest value of 16.0,16.0 is at CC16 @ 2, CC48 @ 104.  0-18 goes from 0.25, 0.5, 0.75, 1, 2, integers up to 16.
       then 0.25 / 0.5 and top one goes up again. So every 19 it increments the bottom to the next.
       ...but it boils down to simple math...interesting to do a more helpful breakdown of the separate Bs on the grid!
    Harmonics CC 17 and 49.  Odd range. 37 and 0 (C is ?DualSin? ) to 89 and 0 ( A&B ?DualSin?) 
        At 44 and 28 C is Square-ish. At 56 and 73 C is Saw-ish. At 63 and 0 its Sin. At 69 and 62 A/B is Saw-ish.
        At 81 and 90 A/B is Square-ish. Etc.
    Detune: CC 18 and 50. (Standard Full range)
    Feedback: CC 19 and 51. (Standard full range)
    MIX: CC 20 and 52....but 52 not used. just 0 = X .... 63 even.... 127 Y
    Phase Reset CC 89.  Values 0 thru 4.  Off, All, Cariers (C), Mods (A+B ?), A+ B2 ??
*/


void build_digitonepad() {
    for ( u8 idx = 0; idx < 8; idx++ ) {
        columnset_superslider(idx, 7, -1, idx+1, 22, 11, 0);
    }
    rowset_octave_mode_etc();

    grid_func[97] = &ToggleDigitoneState;
    change_color(97, 0, 0, 9);
}

void build_digitone_delay() {
    for ( u8 idx = 0; idx < 4; idx++ ) {
        columnset_superslider(idx, 13, -1, idx+1, 0, 16, 0);
    }
    rowset_octave_mode_etc();

    grid_func[97] = &ToggleDigitoneState;
    change_color(97, 0, 0, 9);
}

void build_digitone_chorus() {
    for ( u8 idx = 0; idx < 4; idx++ ) {
        columnset_superslider(idx, 12, -1, idx+1, 0, 11, 22);
    }
    rowset_octave_mode_etc();

    grid_func[97] = &ToggleDigitoneState;
    change_color(97, 0, 0, 9);
}

void build_digitone_reverb() {
    for ( u8 idx = 0; idx < 4; idx++ ) {
        columnset_superslider(idx, 14, -1, idx+1, 22, 0, 0);
    }
    rowset_octave_mode_etc();

    grid_func[97] = &ToggleDigitoneState;
    change_color(97, 0, 0, 9);
}

void build_digitone_lfo() {
    for ( u8 idx = 0; idx < 4; idx++ ) {
        columnset_superslider(idx, 28, -1, idx*2+1, 22, 0, 11);
    }
    for ( u8 idx = 0; idx < 4; idx++ ) {
        columnset_superslider(idx, 29, -1, idx*2+2, 11, 0, 22);
    }
    rowset_octave_mode_etc();

    grid_func[97] = &ToggleDigitoneState;
    change_color(97, 0, 0, 9);
}

void state_digitonepad(StateEvent msg, u8 index, u8 value) {
  switch (msg) {
    case EVENT_EXIT:
      exit_surface();
      break;
    case EVENT_ENTER:
      current_state = LP_DIGITONEPAD_MODE; // for side queries of state...? still haven't needed it anywhere - just may need it?
      build_digitonepad();
      break;
    case EVENT_INPUT:
      (*grid_func[index])(index, value);
      break;
    case EVENT_REDRAW:
      redraw_surface();
      break;
    case EVENT_PRESSURE:
        (*grid_pres[index])(index, value);
        break;
    case EVENT_CLOCK:
    case EVENT_MSG_COUNT:
      break;
  }
}

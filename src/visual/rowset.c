#include "visual/rowset.h"
#include "visual/color.h"
#include "visual/particle.h"
#include "visual/pad.h"
#include "visual/pressure.h"
#include "util/note_func.h"
#include "util/octave.h"
#include "music/diatonic.h"
#include "music/arp.h"
#include "visual/surface.h"

void rowset_R35_arp(u8 basenote, u8 arpmode, u8 padbase) {
    for (u8 adx = 0; adx < 8; adx++) {
        u8 arp_increment = arp_step_triad(adx);
        color c = colorArpTriad(arpmode, adx);
        u8 notecalc = basenote + diatonic_fundemental[arp_increment + arpmode];
        grid_params[padbase + adx].p1 = 0;
        grid_params[padbase + adx].p2 = notecalc;
        grid_func[padbase + adx] = &DoNote;
        grid_pres[padbase + adx] = &NullFunction;
        change_color(padbase + adx, c.r, c.g, c.b );
    }
}

void rowset_octave_state_etc() {
    grid_func[91] = &ChangeOctaveUp;
    grid_func[92] = &ChangeOctaveDown;
    color c = octaveColor(0);
    change_color(91, c.r, c.g, c.b);
    change_color(92, c.r, c.g, c.b);
}

void rowset_circuit_fingerdrum(u8 base, u8 padbase) {  //(idx, 81 - idx * 10);
    for (u8 adx = 0; adx < 8; adx++) {
        color c = {44,5*adx,0};
        u8 cc_calc = base * 8 + adx;
        grid_params[padbase + adx].p1 = 0;
        grid_params[padbase + adx].p2 = cc_calc;
        grid_func[padbase + adx] = &CircuitDrum;
        grid_pres[padbase + adx] = &NullFunction;
        change_color(padbase + adx, c.r, c.g, c.b );
    }
}

void rowset_circuit_sampletune(u8 base, u8 padbase) {  //(idx, 81 - idx * 10);
    for (u8 adx = 0; adx < 8; adx++) {
        color c = {0,5*adx,44};
        u8 cc_calc = base * 16 + adx * 2;
        grid_params[padbase + adx].p1 = 0;
        grid_params[padbase + adx].p2 = cc_calc;
        grid_func[padbase + adx] = &CircuitChromaticSample;
        grid_pres[padbase + adx] = &NullFunction;
        change_color(padbase + adx, c.r, c.g, c.b );
    }
}

void rowset_microtonal_setup(u8 base, u8 padbase) {  
    for (u8 adx = 0; adx < 8; adx++) {
        color c = {11,11,11};
        u8 note_calc = base * 8 + adx + 1;
        if ( padbase + adx == conv64toGrid(microtonal_count - 1)  ) {
            grid_params[padbase + adx].p1 = 1;
            c.r *= 4;
            c.g *= 4;
            c.b *= 4;
        } else {
            grid_params[padbase + adx].p1 = 0;
        }
        grid_params[padbase + adx].p2 = note_calc;
        grid_func[padbase + adx] = &CircuitMicrotonalSet;
        grid_pres[padbase + adx] = &NullFunction;
        change_color(padbase + adx, c.r, c.g, c.b );
    }
}

void rowset_microtonal_notes(u8 base, u8 padbase) {  
    for (u8 adx = 0; adx < 8; adx++) {
        u8 isOn = 1;
        u8 note_calc = base * 8 + adx;
        if ( note_calc >= microtonal_count ) {
            isOn = 0;
        }
        color c = { 11 * isOn, 
                    22 * isOn,
                    44 * isOn
                  };
        grid_params[padbase + adx].p1 = microtonal_notes_on[note_calc];
        grid_params[padbase + adx].p2 = note_calc;
        grid_func[padbase + adx] = &CircuitMicrotonalNotes;
        grid_pres[padbase + adx] = &NullFunction;
        if (isOn && microtonal_notes_on[note_calc] == 0) {
            c.r = 44;
            c.g = 0;
            c.b = 0;
        }
        change_color(padbase + adx, c.r, c.g, c.b );
    }
}
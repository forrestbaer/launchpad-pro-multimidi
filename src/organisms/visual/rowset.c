#include "organisms/visual/rowset.h"
#include "atoms/visual/color.h"
#include "atoms/visual/particle.h"
#include "molecules/visual/pad.h"
#include "atoms/visual/pressure.h"
#include "atoms/function/note_func.h"
#include "molecules/music/diatonic.h"
#include "molecules/music/arp.h"
#include "environment/surface.h"

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

void rowset_octave_mode_etc() {
    grid_func[91] = &ChangeOctaveUp;
    grid_func[92] = &ChangeOctaveDown;
    change_color(91, 33 + 3 * octave[0], 6 * octave[0] + 3, 63);
    change_color(92, 33 + 3 * octave[0], 6 * octave[0] + 3, 63);
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

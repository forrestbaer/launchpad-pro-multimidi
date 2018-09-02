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
        grid_colors[padbase + adx] = c;
        u8 notecalc = basenote + diatonic_fundemental[arp_increment + arpmode];
        grid_params[padbase + adx].p1 = 0;
        grid_params[padbase + adx].p2 = notecalc;
        grid_func[padbase + adx] = &DoNote;
        grid_pres[padbase + adx] = &NullFunction;
        hal_plot_led(TYPEPAD, padbase + adx, c.r, c.g, c.b );
    }
}

void rowset_octave_mode_etc() {
    color c = {33 + 3 * octave, 6 * octave + 3, 63};
    grid_colors[91] = c;
    grid_colors[92] = c;
    grid_func[91] = &ChangeOctaveUp;
    grid_func[92] = &ChangeOctaveDown;
    hal_plot_led(TYPEPAD, 91, c.r, c.g, c.b);
    hal_plot_led(TYPEPAD, 92, c.r, c.g, c.b);
}

void rowset_circuit_fingerdrum(u8 base, u8 padbase) {  //(idx, 81 - idx * 10);
    for (u8 adx = 0; adx < 8; adx++) {
        color c = {44,5*adx,0};
        grid_colors[padbase + adx] = c;
        u8 cc_calc = base * 8 + adx;
        grid_params[padbase + adx].p1 = 0;
        grid_params[padbase + adx].p2 = cc_calc;
        grid_func[padbase + adx] = &CircuitDrum;
        grid_pres[padbase + adx] = &NullFunction;
        hal_plot_led(TYPEPAD, padbase + adx, c.r, c.g, c.b );
    }
}

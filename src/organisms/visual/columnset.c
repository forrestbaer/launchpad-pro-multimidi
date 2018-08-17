#include "organisms/visual/columnset.h"
#include "atoms/visual/color.h"
#include "atoms/visual/particle.h"
#include "molecules/visual/pad.h"
#include "atoms/visual/pressure.h"
#include "atoms/function/note_func.h"
#include "molecules/music/diatonic.h"
#include "molecules/music/arp.h"
#include "environment/surface.h"

void columnset_R35_arp(u8 basenote, u8 arpmode, u8 padbase) {
    for (u8 adx = 0; adx < 8; adx++) {
        u8 arp_increment = arp_step_triad(adx);
        color c = {63 - adx * 6, 63, 63};
        grid_colors[padbase + 10 * adx] = c;  //not good enough - just a test
        u8 notecalc = basenote + diatonic_fundemental[arp_increment + arpmode];
        //grid_func[padbase + 10 * adx] = &note_func_array[notecalc];  //(*DoNote)(basenote + diatonic_fundemental[arp_increment + arpmode], index, value);
        grid_params[padbase + 10 * adx].p1 = 0;
        grid_params[padbase + 10 * adx].p2 = notecalc;
        grid_func[padbase + 10 * adx] = &DoNote;  //(*DoNote)(0, notecalc, 128);
        grid_pres[padbase + 10 * adx] = &NullFunction;
        hal_plot_led(TYPEPAD, padbase + 10 * adx, c.r, c.g, c.b );
    }

    //grid_func[j*10 + i] = &FilledDoMore;
}

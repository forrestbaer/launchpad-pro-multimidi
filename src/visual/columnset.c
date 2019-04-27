#include "visual/columnset.h"
#include "visual/color.h"
#include "visual/particle.h"
#include "visual/pad.h"
#include "visual/pressure.h"
#include "util/note_func.h"
#include "midi/cc.h"
#include "music/diatonic.h"
#include "music/arp.h"
#include "visual/surface.h"

void columnset_R35_arp(u8 basenote, u8 arpmode, u8 padbase) {
    for (u8 adx = 0; adx < 8; adx++) {
        u8 arp_increment = arp_step_triad(adx);
        color c = colorArpTriad(arpmode, adx);
        u8 notecalc = basenote + diatonic_fundemental[arp_increment + arpmode];
        grid_params[padbase + 10 * adx].p1 = 0;
        grid_params[padbase + 10 * adx].p2 = notecalc;
        grid_func[padbase + 10 * adx] = &DoNote;
        grid_pres[padbase + 10 * adx] = &NullFunction;
        change_color(padbase + 10 * adx, c.r, c.g, c.b );
    }
}

void columnset_MCP_arp(u8 basenote, u8 arpmode, u8 padbase) {
    for (u8 adx = 0; adx < 8; adx++) {
        u8 arp_increment = arp_step_mcp(adx);
        color c = colorArpMcp(arpmode, adx);
        u8 notecalc = basenote + diatonic_fundemental[arp_increment + arpmode];
        grid_params[padbase + 10 * adx].p1 = 0;
        grid_params[padbase + 10 * adx].p2 = notecalc;
        grid_func[padbase + 10 * adx] = &McpNote;
        grid_pres[padbase + 10 * adx] = &NullFunction;
        change_color(padbase + 10 * adx, c.r, c.g, c.b );
    }
}

void columnset_superslider(u8 midichannel, u8 cc1, s8 cc2, u8 column, u8 r, u8 g, u8 b) {
    // IDEA: new level of slider for LPP: 8 distinct points like normal, but ability to use aftertouch/Pressure
    // to mix from static 8 points.
    const u8 arraySlide[8] = {0,31,46,63,78,96,111,127};
    for (u8 cdx = 1; cdx < 9; cdx++) {
        
        grid_params[cdx * 10 + column].p1 = midichannel;
        grid_params[cdx * 10 + column].p7 = 0;  // this is like the "current value"
        // this will hold the pressure value and use the others in the column to determine result
        // if only then it goes to the hard value. if 2 in column then it finds balance between the 2 and blends the 2 hard values
        // if 3+ holding pressure in column then ? but try to handle gracefully.
        // note: could hold row 1 and row 8 and blend between those or neighbors for higher precision
        // ALSO: draw slider results in a meaningful way.
        grid_params[cdx * 10 + column].p2 = arraySlide[cdx - 1];
        grid_params[cdx * 10 + column].p3 = cc1;
        grid_params[cdx * 10 + column].p4 = cc2;  // cc2 is for those synth parameters with extra precision. Different synths handle this differently
        grid_params[cdx * 10 + column].p5 = 0; // this is for "Last or prior p1 (pressure) value" to determine direction of action flow
        grid_params[cdx * 10 + column].p6 = 0; // this "Marks Dirty" = after goes into multipoint pressure change don't allow return to single until pressure goes to zero
        
        grid_func[cdx * 10 + column] = &SliderHit;  // this may do nothing? SliderPressure could handle it all (maybe)
        grid_pres[cdx * 10 + column] = &SliderPressure;
        // PROBLEM: as you release, the last pressure is affected. can screw this all up. Possible solution:
        // when it sees both pressures are reducing, stop the calculation. or other button locks it.
        change_color(cdx * 10 + column, r, g, b );
    }
}

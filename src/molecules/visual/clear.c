#include "molecules/visual/clear.h"

void clear_leds()
{
    for (u8 i = LP_FIRST_BUTTON; i <= LP_LAST_BUTTON; i++)
    {
        hal_plot_led(TYPEPAD, i, 0x00, 0x00, 0x00);
    }
}

void clear_pad_leds()
{
    u8 index = FIRST_PAD;
    for (u8 i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
        if (i > 0 && i % GRID_SIZE == 0) {
            index += ROW_GAP;
        }
        hal_plot_led(TYPEPAD, index, 0x00, 0x00, 0x00);
        index++;
    }
}

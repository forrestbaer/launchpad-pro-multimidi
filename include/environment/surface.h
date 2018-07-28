#ifndef surface_h
#define surface_h

#include "app.h"
#include "atoms/visual/color.h"
#include "atoms/visual/particle.h"
#include "molecules/visual/pad.h"
/*
The active / current Surface of All Pads, their colors, and function, PLUS a Counter, toggle booleans of a variety of usage, ?other states?
. Not just the 64 note grid, the "sidebars" too

!!! What if every PAD held up to 4 Functions?!?!?!?!?! Example: Note, Animation Trigger, CC change, ??  !!!!
--- Probably best in a funcStack() is a function that helps point to 1 to 4 functions to manage the bunch---

An Array of 100 (?98?) Pointers to Functions & An Array of 100 (98?) Colors
(a few are blank?!?! or used as other holders of info...it seems Novation set it up so the "missing" ones from 100 fail silently if sent color. fine for our purposes)

Safe Array of Function Pointers aka Jump Tables...
A much better way to code this that avoids these problems is as follows

void test(uint8_t const jump_index)
{
    static void (*pf[])(void) = {fna, fnb, fnc, ..., fnz};

    if (jump_index < sizeof(pf) / sizeof(*pf))
    {
        //Call the function specified by jump_index
        pf[jump_index]();
    }
}

*/
extern color grid_colors[BUTTON_COUNT];
extern particle particles[64]; //grid_particles aren't positioned by Index per se but by attribute to avoid animation overwriting
//extern void (*grid_func[BUTTON_COUNT])(void);
extern void (*grid_func[BUTTON_COUNT])(u8, u8);

void recrsvDirFill(u8 dirInt, u8 index, u8 recrsvDepth);
void DoMore(u8 setting, u8 index, u8 value);
void FilledDoMore(u8 index, u8 value);

void DoLess(u8 setting, u8 index, u8 value);
void FilledDoLess(u8 index, u8 value);

void prep_surface();

#endif /* surface_h */

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

typedef struct {
  u8 p1,p2,p3,p4,p5,p6;
} GridParams;  // different grid_func will use these in different ways

extern color grid_colors[BUTTON_COUNT];
extern particle particles[64]; //grid_particles aren't positioned by Array Index (tried that) but by attribute to avoid animation overwriting
extern void (*grid_func[BUTTON_COUNT])(u8, u8);
extern void (*grid_pres[BUTTON_COUNT])(u8, u8);
extern GridParams grid_params[BUTTON_COUNT]; // this holds each pad's parameters. Easier than trying to store them in the grid_func - that was a nightmare
extern u8 octave;  // octave 2 is like C0 a.k.a. midi note 24 (easier math, no negatives). By default octave is set to 5 which = Middle C (C3) midi note 60
extern u8 keyscale; // 0 is C, 1 is C#, etc.  Why? Many "Instruments" are in a scale and this allows different scales
extern u8 modal; // 0 is Major (Ionian), 1 is Dorian, etc. ... past 6 (Locrian) could do exotics...but may need a different system for it.

void exit_surface();
void redraw_surface();
void prep_surface();

#endif /* surface_h */

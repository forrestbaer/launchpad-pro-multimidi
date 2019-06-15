#ifndef surface_h
#define surface_h

#include "app.h"
#include "visual/color.h"
#include "visual/particle.h"
#include "visual/pad.h"
/*
The active / current Surface of All Pads, their colors, and function, PLUS a Counter, toggle booleans of
a variety of usage, ?other states?
Not just the 64 note grid, the "sidebars" too

!!! What if every PAD held up to 4 Functions?!?!?!?!?! Example: Note, Animation Trigger, CC change, ??  !!!!
--- Probably best in a funcStack() is a function that helps point to 1 to 4 functions to manage the bunch---

An Array of 100 (?98?) Pointers to Functions & An Array of 100 (98?) Colors
(a few are blank?!?! or used as other holders of info...it seems Novation set it up so the "missing" ones from 100 fail silently if sent color. fine for our purposes)

*/

typedef struct {
  u8 p1,p2,p3,p4,p5,p6,p7,p8;
} GridParams;  // different grid_func will use these in different ways

extern color grid_colors[BUTTON_COUNT];
extern particle particles[64]; //grid_particles aren't positioned by Array Index (tried that) but by attribute to avoid animation overwriting
extern void (*grid_func[BUTTON_COUNT])(u8, u8);
extern void (*grid_pres[BUTTON_COUNT])(u8, u8);
extern GridParams grid_params[BUTTON_COUNT]; // this holds each pad's parameters. Easier than trying to store them in the grid_func - that was a nightmare
extern heldnote heldnotes[BUTTON_COUNT]; //any note goes in, NOTEOFF comes from this... for octave change, complex manipulations, etc.
  //now keeps track of multiple octave controls!!
extern u8 octave[2];  // octave 2 is like C0 a.k.a. midi note 24 (easier math, no negatives). By default octave is set to 5 which = Middle C (C3) midi note 60
// see diatonic.c for a list of the scales/modes that line up to modal memory_store[MEM_SCALE]
// memory_store[MEM_OFFSET_STATE] =  like offset on LPP factory scale mode. 0 = ? no offset just natural note progression, 7 = octaves lined up??
// memory_store[MEM_SCALE_STATE_ACTIVE] 0 = original LPP before scale mode, 1 = scale mode, may add more types
extern u8 selectedSlot;
extern u8 mcpSet1;
extern u8 mcpSet2; // 2 groups of settings for channel options for the MCP mode

void exit_surface();
void change_color(u8 index, u8 r, u8 g, u8 b);
void red_notes();
void red_notes_microtonal();
void redraw_surface();
void prep_surface();

#endif /* surface_h */

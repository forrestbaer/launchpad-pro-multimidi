#ifndef surface_h
#define surface_h

#include "app.h"
#include "atoms/visual/color.h"
#include "molecules/visual/pad.h"
/*
The active / current Surface of All Pads, their colors, and function, PLUS a Counter, toggle booleans of a variety of usage, ?other states?
. Not just the 64 note grid, the "sidebars" too

!!! What if every PAD held up to 4 Functions?!?!?!?!?! Example: Note, Animation Trigger, CC change, ??  !!!!
--- Probably best in a funcStack() is a function that helps point to 1 to 4 functions to manage the bunch---

An Array of 100 (?98?) Pointers to Functions & An Array of 100 (98?) Colors (a few are blank?!?! or used as other holders of info)

Use this kind...to assign but do it in an array
    // 2.5 calling a function using a function pointer
    int result2 = (*pt2Function) (12, 'a', 'b');          // C
Also see http://www.newty.de/fpt/fpt.html#chapter2  at 2.8... but that's confusing and I think it's easier than that.


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

// ! But I may need to have the array not static and outside function... maybe more "dangerous" but should be ok.
*/
extern color grid_colors[BUTTON_COUNT];
//extern void (*grid_func[BUTTON_COUNT])(void);
extern void (*grid_func[BUTTON_COUNT])(u8, u8);

void recrsvDirFill(u8 dirInt, u8 index, u8 recrsvDepth);
void DoMore(u8 setting, u8 index, u8 value);
void FilledDoMore(u8 index, u8 value);

void DoLess(u8 setting, u8 index, u8 value);
void FilledDoLess(u8 index, u8 value);

void prep_surface();

//void fna();

#endif /* surface_h */

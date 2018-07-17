#ifndef surface_h
#define surface_h
/*
The active / current Surface of All Pads, their colors, and function.

An Array of 100 (?98?) Pointers to Functions & An Array of 100 (98?) Colors (a few are blank?!?! or used as other holders of info)
<< This could fall under surface.h and .c >>
Use this kind...to assign but do it in an array
    // 2.5 calling a function using a function pointer
    int result1 = pt2Function    (12, 'a', 'b');          // C short way
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

// ! But I may need to have the array not static and outside function... maybe more dangerous but should be ok.
*/
#endif /* surface_h */

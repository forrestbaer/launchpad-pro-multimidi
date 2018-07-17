#ifndef state_h
#define state_h

//The concept of the whole app is simpler and yet more advanced and complete:
/*
There is still the master state of the app, but more importantly the grid is set up as
An Array of 100 (?98?) Pointers to Functions & An Array of 100 (98?) Colors (a few are blank?!?! or used as other holders of info)
<< This could fall under surface.h and .c >>
Use this kind...to assign but do it in an array
    // 2.5 calling a function using a function pointer
    int result1 = pt2Function    (12, 'a', 'b');          // C short way
    int result2 = (*pt2Function) (12, 'a', 'b');          // C
Also see http://www.newty.de/fpt/fpt.html#chapter2  at 2.8... but that's confusing and I think it's easier than that.

Separate States may become less important as Every State will be the same type of thing
...basically an open area where all the functions are available
Some actions may change just 1 rowset or areaset instead of the whole Page

Before building it as the music system it will be, build it as a game where Pads do functions on Press:
1. Change the Pad
2. Change other Pad(s).. possibly sets of row, column, all, random, one, (above, below, right, left IF exists logic)
3. Trigger Animation of Pads (be able to set tempo or at least have default BPM so animation runs based on tempo) (how to run it on it's own without needing a thread?? Callback on timer function~~~)
4. Change state

Maybe tie color to the type of function it performs

Next tie a music function to these actions.

Then build out real system.
*/

// let's do a proper state machine on this one.... debating to do it simple or for real.  Accessibility vs. Sophistication
// if simple, could use state in 2 places: Action based and Timer based. Something tells me the simple way will still get spagetti code.

// on enter
// while in
// on exit

#endif /* state_h */

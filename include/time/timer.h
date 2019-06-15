#ifndef timer_h
#define timer_h
/*
 handles the master clock and time event loop
*/
#include <math.h>

extern u8 animCnt;
extern d8 preciseTime;

void core_clock();

#endif /* timer_h */

#ifndef color_h
#define color_h

#include "app.h"

/* may just be a place to put the color array... but may go for raw rgb values */
typedef struct {
   u8    r;
   u8    g;
   u8    b;
} color;

color colorRanger(u8 input, u8 type);
color color8(u8 input, u8 type);

#endif /* color_h */

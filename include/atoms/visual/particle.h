#ifndef particle_h
#define particle_h

#include "app.h"

typedef struct {
   u8    positionIndex;
   u8    r;
   u8    g;
   u8    b;
   u8    nextDir;
   u8    behavior;
   u8    sequence;
} particle;

void moveParticles();
void addParticle(particle p);
void particleBehavior(u8 behavior, u8 *nextDir, u8 *sequence);

#endif /* particle_h */

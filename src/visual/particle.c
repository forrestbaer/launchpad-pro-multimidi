#include "visual/particle.h"
#include "visual/pad.h"
#include "visual/surface.h"

void moveParticles() {
  u8 position = 0;
  for (u8 pdx = 0; pdx < 64; pdx++) {
    position = particles[pdx].positionIndex;
    if ( position == 0 ) {  // like a nulled out, unused particle
      continue;
    }
    //clear old particle spots
    hal_plot_led(TYPEPAD, position, grid_colors[position].r, grid_colors[position].g, grid_colors[position].b  );
    u8 newPos = directional(particles[pdx].nextDir, position);
    if (newPos != 0) {
        position = newPos;
        particles[pdx].positionIndex = position;
        particleBehavior(particles[pdx].behavior, &particles[pdx].nextDir, &particles[pdx].sequence);
        if ( particles[pdx].sequence > 7 ) {
          // right now sequence 8 is delete order.
          particles[pdx].r = particles[pdx].g = particles[pdx].b = particles[pdx].nextDir = particles[pdx].positionIndex = particles[pdx].behavior = particles[pdx].sequence = 0;
        }
    } else {
        // hit an edge so remove particle
        particles[pdx].r = particles[pdx].g = particles[pdx].b = particles[pdx].nextDir = particles[pdx].positionIndex = particles[pdx].behavior = particles[pdx].sequence = 0;
    }
  }
  //draw updated set
  for (u8 pdx = 0; pdx < 64; pdx++) {
      if (particles[pdx].positionIndex != 0) {
        hal_plot_led(TYPEPAD, particles[pdx].positionIndex, particles[pdx].r, particles[pdx].g, particles[pdx].b  );
      }
  }
}


void addParticle(particle p) {
    //search for the next empty slot in the particles[] and fill it. empty is easily defined as positionIndex == 0
    u8 pdx = 0;
    while(particles[pdx].positionIndex != 0 && pdx < 64) {
      pdx++;
    }
    particles[pdx] = p;
    hal_plot_led(TYPEPAD, particles[pdx].positionIndex, particles[pdx].r, particles[pdx].g, particles[pdx].b  );
}

void particleBehavior(u8 behavior, u8 *nextDir, u8 *sequence) { //to make particle behavior more than basic,
    // sequence was introduced to vary the behavior over time.
    u8 newDir = *nextDir;
    switch (behavior) {
      case 0:
        *sequence = 0;
        *nextDir = newDir;
        break;
      case 1:  //curve Clockwise
        if (*sequence % 2 == 0) {
          newDir++;
          if (newDir > 7) { newDir = 0; }
        }
        *nextDir = newDir;
        *sequence = *sequence + 1;
        if (*sequence > 8) {
          *sequence = 0;
        }
        break;
      case 2:  //curve CounterClockwise
        if (*sequence % 2 == 0) {
          if (newDir == 0) {
            newDir = 7;
          } else {
            newDir--;
          }
        }
        *nextDir = newDir;
        *sequence = *sequence + 1;
        if (*sequence > 8) {
          *sequence = 0;
        }
        break;
    }
    return;
}

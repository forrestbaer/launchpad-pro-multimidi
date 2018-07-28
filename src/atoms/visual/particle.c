#include "atoms/visual/particle.h"
#include "molecules/visual/pad.h"
#include "environment/surface.h"

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
        //drawing now is no good as pads shifted away from may happen before or after and may clear
    } else {
        // hit an edge so remove particle
        particles[pdx].r = particles[pdx].g = particles[pdx].b = particles[pdx].nextDir = particles[pdx].positionIndex = 0;
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

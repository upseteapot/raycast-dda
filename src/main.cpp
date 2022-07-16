#include "graphics/simulation.hpp"


int main(void)
{
  Simulation sim;
  sim.create(1920, 1080, "Raycast");
  sim.main_loop();
  
  return 0;
}


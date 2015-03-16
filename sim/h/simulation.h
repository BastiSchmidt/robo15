#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <stdlib.h>
#include <time.h>
#include "Configuration.h"


void init_sim_rnd();

int move_d(int direction);

void discover();

int direction_detect(int given_intersection, int wanted_direction);

void print_matrix();

#endif /* SIMULATION_H_ */
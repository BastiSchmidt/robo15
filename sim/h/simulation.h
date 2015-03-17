#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "Configuration.h"

void init_sim_rnd();

int turn_left();

int turn_right();

int go_straight();

int move_d(int direction);

void discover();

int direction_detect(int given_intersection, int wanted_direction);

void print_matrix();

#endif /* SIMULATION_H_ */
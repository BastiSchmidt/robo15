#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "Configuration.h"

void init_sim_rnd();

int turn_left();

int turn_right();

int go_straight();

int move_d(int direction);

int scan();

#endif /* SIMULATION_H_ */

#ifndef _ROBO15_ALGORITHM_H_
#define _ROBO15_ALGORITHM_H_

#include "Configuration.h"

int dfs();

void discover();

int direction_detect(int given_intersection, int wanted_direction);

int node_visited(int direction);

int turn_d(int direction);

void print_matrix();

#endif //_ROBO15_ALGORITHM_H_

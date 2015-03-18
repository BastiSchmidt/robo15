#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define	DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

// user headers
#include "Communication.h"
#include "Urlcode.h"
#include "RobotProxy.h"
#include "simulation.h"
#include "algorithm.h"

// define server config here
#define IP "localhost"
#define PORT "8080"

// define your GROUP ID here (no umlauts!)
#define GROUPID "gruppe29"

// define server URL
#define URL "http://" IP ":" PORT "/query?id=" GROUPID "&values="

// define maze size here
#define MAZE_WIDTH 6
#define MAZE_HEIGHT 6

#define TOKEN_AIM 3

struct coord current_position; //global current position of bot

//Current orientation of bot
int orientation;

//Naive approach for creating a simple map of known nodes
//offset of MAZE_WIDTH + 1 to make sure we have enough space for every start point
//4 layers to save available directions, visited directions and flags for dfs
// and bfs
int matrix[2*MAZE_WIDTH + 2][2*MAZE_HEIGHT + 2][4];



#endif /* CONFIGURATION_H_ */

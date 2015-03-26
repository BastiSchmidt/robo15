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
#define MAZE_WIDTH 7
#define MAZE_HEIGHT 7

#define TOKEN_AIM 3

//Current orientation of bot
int orientation;

//map of pointers to node objects
struct node *ptrmap[2 * MAZE_WIDTH][MAZE_HEIGHT + 2];

int tokencount;
int discovered_everything;

struct instructions *global_instructions;

#endif /* CONFIGURATION_H_ */

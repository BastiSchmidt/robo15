#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define	DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// user headers
#include "Communication.h"
#include "Urlcode.h"
#include "RobotProxy.h"
#include "simulation.h"

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

//Absolute coordinates
int x_pos;
int y_pos;

#endif /* CONFIGURATION_H_ */

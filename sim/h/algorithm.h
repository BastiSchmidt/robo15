#ifndef _ROBO15_ALGORITHM_H_
#define _ROBO15_ALGORITHM_H_

#include "Configuration.h"

//Absolute coordinates
typedef struct coord{
    int x;
    int y;
} coord;

struct coord current_position;

typedef struct node *maze;
typedef struct node{
    struct coord position;
    maze north;
    maze south;
    maze east;
    maze west;
    bool visited;
} node;

struct node *current_node;

//Matrix of Pointers to nodes
struct node *ptrmap[2 * 7 + 2][2 * 7 + 2]; //TODO: replace static size!

void init();

void discover();

int direction_detect(int given_intersection, int wanted_direction);

int node_visited(int direction);

int turn_d(int direction);

struct node *create_node();

void print_matrix(int layer);

void print_ptrmap();

#endif //_ROBO15_ALGORITHM_H_

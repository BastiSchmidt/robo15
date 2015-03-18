#ifndef _ROBO15_ALGORITHM_H_
#define _ROBO15_ALGORITHM_H_

#include "Configuration.h"

//Absolute coordinates
typedef struct coord{
    int x;
    int y;
} coord;

struct coord current_position;

//Current orientation of bot
int orientation;

typedef struct node *maze;
typedef struct node{
    struct coord position;
    maze north;
    maze south;
    maze east;
    maze west;
    bool visited;
} node;

//Matrix of Pointers to nodes
struct maze ptrmap[2*MAZE_HEIGHT + 2][2*MAZE_WIDTH + 2];

//einfach verkette Liste als Warteschlange im bfs
typedef struct element *next;
typedef struct element{
    struct coord node_position;
};

void queue_append();
void queue_remove_first();

void discover();

int direction_detect(int given_intersection, int wanted_direction);

int node_visited(int direction);

int turn_d(int direction);

void print_matrix(int layer);

struct coord bfs_closest_unvisited_node();
#endif //_ROBO15_ALGORITHM_H_

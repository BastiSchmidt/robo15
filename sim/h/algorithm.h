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
    maze compass[4];
    bool visited;
} node;

struct node *current_node;


//einfach verkette Liste als Warteschlange im bfs
typedef struct element *list;
typedef struct element{
    struct coord node_position;
    list next;
} element;

void list_append(struct element **start, struct coord discovered);

void list_remove_first(struct element **start);

void destroy_list(struct element **start);

struct node *ptrmap[2 * 7 + 2][2 * 7 + 2]; //TODO: replace static size!

void init();

void discover();

int direction_detect(int given_intersection, int wanted_direction);

int node_visited(int direction);

int turn_d(int direction);

struct node *create_node();

struct coord bfs_closest_unvisited_node();

struct coord shift_coordinates(struct coord old, int direction);

void print_matrix(int layer);

void print_ptrmap();

#endif //_ROBO15_ALGORITHM_H_

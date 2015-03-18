#include "../h/algorithm.h"



//Discover surrounding connected nodes
void discover(){
    //save readings in matrix
    matrix[current_position.y + MAZE_HEIGHT][current_position.x + MAZE_WIDTH][0] =
            scan();
}

//Returns 1 if the wanted cardinal direction is available at a intersection,
//0 if not
int direction_detect(int given_intersection, int wanted_direction) {
    //Northern node?
    if ((given_intersection % 0x20 == 0x10) && wanted_direction == NORTH) {
        return 1;
    }

    //Eastern node?
    else if ((given_intersection >= 0x80) && wanted_direction == EAST) {
        return 1;
    }

    //Southern node?
    else if ((given_intersection % 0x40 == 0x20 ||
            given_intersection % 0x40 == 0x30) && wanted_direction == SOUTH) {
        return 1;
    }

    //Western node?
    else if (
            ((given_intersection >= 0x40 &&
                    given_intersection <= 0x70) ||
                given_intersection >= 0xC0) &&
            wanted_direction == WEST
            ){
        return 1;
    }

    return 0;
}

//returns if the node in a specific direction relative to the current position
// has been visited already
int node_visited(int direction){
    int x = current_position.x;
    int y = current_position.y;

    switch (direction){
        case NORTH: y += 1;
            break;
        case EAST: x += 1;
            break;
        case SOUTH: y -= 1;
            break;
        case WEST: x -= 1;
            break;
    }

    return matrix[y + MAZE_HEIGHT][x + MAZE_WIDTH][2];
}

//turn bot in a specific direction
int turn_d(int direction){
    while (orientation != direction){
        turn_left();
    }
    return ROBOT_SUCCESS;
}

//outputs matrix to stdout, Attention: mirrored at y-axis!
void print_matrix(int layer){
    int i, j;
    for(i = 2 * MAZE_WIDTH + 1; i >= 0 ; i--){
        for(j = 0; j < 2* MAZE_WIDTH + 2; j++) {
            if (matrix[i][j][layer] == 0) {
                printf("   ");
            } else {
                printf("%02x ", matrix[i][j][layer]);
            }
        }
        printf("\n");
    }
}


struct coord bfs_closest_unvisited_node() {
    struct element *init;
    init = NULL;
    struct coord wanted;
    int i = current_position.x;
    int j = current_position.y;
    while (true) {
        if (ptrmap[i + MAZE_WIDTH][j + MAZE_HEIGHT]-> east != NULL && ptrmap[i + MAZE_WIDTH][j + MAZE_HEIGHT] -> east -> visited == 0) {
            wanted.x = i + 1;
            wanted.y = j;
            return wanted; //dann returne die Koordinaten auf der ptrmap davon
        }
        if (ptrmap[i + MAZE_WIDTH][j + MAZE_HEIGHT]->south != NULL && ptrmap[i + MAZE_WIDTH][j + MAZE_HEIGHT]-> south -> visited == 0) {
            wanted.x = i;
            wanted.y = j -1;
            return wanted;
        }
        if (ptrmap[i + MAZE_WIDTH][j + MAZE_HEIGHT]-> west != NULL && ptrmap[i + MAZE_WIDTH][j + MAZE_HEIGHT]-> west -> visited == 0) {
            wanted.x = i - 1;
            wanted.y = j;
            return wanted;
        }
        if (ptrmap[i + MAZE_WIDTH][j + MAZE_HEIGHT]-> north != NULL && ptrmap[i + MAZE_WIDTH][j + MAZE_HEIGHT]-> north -> visited == 0) {
            wanted.x = i;
            wanted.y = j + 1;
            return wanted;
        }
    }
}


void append(struct element **start, struct coord discovered) {

    struct element *iter = *start;

    if (*start == NULL) {
        *start = malloc(sizeof(struct element));
        *start->node_position = discovered;
        *start->next = NULL;
        return;
    }
    else {
        while (iter->next != NULL) {
            iter = iter->next;
        }
        iter->next = malloc(sizeof(struct element));
        iter->next->node_position = discovered;
        iter->next->next = NULL;
        return;
    }
}
#include "../h/algorithm.h"


//Discover surrounding connected nodes
void discover(){
    //save readings in matrix
    matrix[y_pos + MAZE_HEIGHT][x_pos + MAZE_WIDTH] =
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

//outputs matrix to stdout, Attention: mirrored at y-axis!
void print_matrix(){
    int i, j;
    for(i = 2 * MAZE_WIDTH + 1; i >= 0 ; i--){
        for(j = 0; j < 2* MAZE_WIDTH + 2; j++) {
            if (matrix[i][j] == 0) {
                printf("   ");
            } else {
                printf("%02x ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}
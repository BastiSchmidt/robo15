#include "../h/simulation.h"

//Place the bot at a (pseudo) random, valid position
//for better simulation of real start conditions
void init_sim_rnd() {

    srand(time(NULL));
    int r;

    //yields an int between 0 and MAZE_WIDTH(inclusive)
    r = rand() % (MAZE_WIDTH + 1);

    if(Robot_Move(r,0)==ROBOT_FAIL) {
        printf("Trying different position...\n");
        init_sim_rnd(); //recursion is its own reward
        //TODO: abort conditions!
    } else {
        x_pos = r; //Update position on successful placement
        y_pos = 0;
    }
}

//Move in a given direction, no detection/abort in case of missing edge!
int move_d(int direction){
    switch (direction){
        case NORTH: y_pos += 1;
            break;
        case EAST: x_pos += 1;
            break;
        case SOUTH: y_pos -= 1;
            break;
        case WEST: x_pos -= 1;
            break;
    }
    return(Robot_Move(x_pos, y_pos));
}

//Discover surrounding connected nodes
void discover(){
    //save readings in matrix
    matrix[y_pos + MAZE_HEIGHT][x_pos + MAZE_WIDTH] =
            Robot_GetIntersections();
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
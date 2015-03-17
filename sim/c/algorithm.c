#include "../h/algorithm.h"

int dfs() {
    int last_d;
    int new_way_found = 0;
    int tokencount = 0;

    while (tokencount < TOKEN_AIM) {
        discover();
        matrix[y_pos + MAZE_HEIGHT][x_pos + MAZE_WIDTH][2] = true;
        int i, d = 8;
        for (i = 0; i < 4; i++) {
            d = d * 2;
            if (direction_detect(scan(), d) && (!node_visited(d)) ) {
                turn_d(d);
                if (go_straight() == ROBOT_TOKENFOUND){
                    tokencount += 1;
                }
                new_way_found = true;
                break;
            }

        last_d = d;
        }
        print_matrix(2);
    }
}


//Discover surrounding connected nodes
void discover(){
    //save readings in matrix
    matrix[y_pos + MAZE_HEIGHT][x_pos + MAZE_WIDTH][0] =
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

int node_visited(int direction){
    int x = x_pos;
    int y = y_pos;

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

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

//Move in a given direction, currently no detection/abort in case of missing edge!
int move_d(int direction){
    switch (direction){
        case NORTH: return(Robot_Move(x_pos, y_pos + 1));
        case EAST: return(Robot_Move(x_pos + 1, y_pos));
        case SOUTH: return(Robot_Move(x_pos, y_pos - 1));
        case WEST: return(Robot_Move(x_pos - 1, y_pos));
    }
}

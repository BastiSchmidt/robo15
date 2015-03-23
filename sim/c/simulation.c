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
        current_position.x = r; //Update position on successful placement
        current_position.y = 0;
    orientation = 0;
    Robot_Move(current_position.x,current_position.y);
    }
}

int turn_left(){
    switch (orientation){
        case 0: orientation = 3;
            break;
        case 1: orientation = 0;
            break;
        case 2: orientation = 1;
            break;
        case 3: orientation = 2;
            break;
        case NORTH: orientation = WEST;
            break;
        case EAST: orientation = NORTH;
            break;
        case SOUTH: orientation = EAST;
            break;
        case WEST: orientation = SOUTH;
            break;
        default:
            return ROBOT_FAIL;
    }
    return ROBOT_SUCCESS;
}

int turn_right(){
    switch (orientation){
        case 0: orientation = 1;
            break;
        case 1: orientation = 2;
            break;
        case 2: orientation = 3;
            break;
        case 3: orientation = 0;
            break;
        case NORTH: orientation = EAST;
            break;
        case EAST: orientation = SOUTH;
            break;
        case SOUTH: orientation = WEST;
            break;
        case WEST: orientation = NORTH;
            break;
        default:
            return ROBOT_FAIL;
    }
    return ROBOT_SUCCESS;
}

//go forward in current orientation, regardless of edge or no edge present
int go_straight(){
    int result = move_d(orientation);
    current_node = ptrmap[current_position.x + MAZE_WIDTH]
            [current_position.y + MAZE_HEIGHT];
    if (result == ROBOT_TOKENFOUND) tokencount += 1;
    return result;
}


//Move in a given direction, no detection/abort in case of missing edge!
int move_d(int direction){
    switch (direction){
        case 0: current_position.y += 1;
            break;
        case 1: current_position.x += 1;
            break;
        case 2: current_position.y -= 1;
            break;
        case 3: current_position.x -= 1;
            break;
        case NORTH: current_position.y += 1;
            break;
        case EAST: current_position.x += 1;
            break;
        case SOUTH: current_position.y -= 1;
            break;
        case WEST: current_position.x -= 1;
            break;

    }
    return(Robot_Move(current_position.x, current_position.y));
}

//return intersection at current position
int scan(){
    return Robot_GetIntersections();
}

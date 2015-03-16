#include "../h/simulation.h"

//Place the bot at a (pseudo) random, valid position
//for better simulation of real start conditions
void init_sim_rnd() {

    srand(time(NULL));
    int r;

    //yields an int between 0 and MAZE_WIDTH(inclusive)
    r = rand() % (MAZE_WIDTH + 1);

    if(Robot_Move(r,0)==0) {
        printf("Trying different position...\n");
        init_sim_rnd(); //recursion is its own reward
        //TODO: abort conditions!
    }
}
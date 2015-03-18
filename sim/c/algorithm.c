#include "../h/algorithm.h"

void init(){
    int i, j;
    for(i = 0; i < 2 * MAZE_HEIGHT + 2; i++){
        for(j = 0; j < 2* MAZE_WIDTH + 2; j++) {
            ptrmap[i][j] = NULL;
        }
    }
    current_node = create_node();
    ptrmap[current_position.x + MAZE_WIDTH][current_position.y + MAZE_HEIGHT] =
            current_node;
}

//Discover surrounding connected nodes
void discover(){
    //save readings in matrix
    matrix[current_position.y + MAZE_HEIGHT][current_position.x + MAZE_WIDTH][0] =
            scan();

    if (!current_node->visited){
        int new_intersection = 0;
        new_intersection = scan();

        if (direction_detect(new_intersection,NORTH)
                && (ptrmap[current_position.x + MAZE_WIDTH]
                [current_position.y + 1 + MAZE_HEIGHT] == NULL) ){
            maze northern_node = create_node();
            printf("Adding northern node...\n");
            current_node->north = northern_node;
            northern_node->south = current_node;
            ptrmap[current_position.x + MAZE_WIDTH]
                    [current_position.y + 1 + MAZE_HEIGHT] = northern_node;
        }

        if (direction_detect(new_intersection,EAST)
                && (ptrmap[current_position.x + 1 + MAZE_WIDTH]
                [current_position.y + MAZE_HEIGHT] == NULL)){
            maze eastern_node = create_node();
            printf("Adding eastern node...\n");
            current_node->east = eastern_node;
            eastern_node->west = current_node;
            ptrmap[current_position.x + 1 + MAZE_WIDTH]
                    [current_position.y + MAZE_HEIGHT] = eastern_node;
        }

        if (direction_detect(new_intersection,SOUTH)
                && (ptrmap[current_position.x + MAZE_WIDTH]
                [current_position.y - 1 + MAZE_HEIGHT] == NULL)){
            maze southern_node = create_node();
            printf("Adding southern node...\n");
            current_node->south = southern_node;
            southern_node->north = current_node;
            ptrmap[current_position.x + MAZE_WIDTH]
                    [current_position.y - 1 + MAZE_HEIGHT] = southern_node;
        }

        if (direction_detect(new_intersection,WEST)
                && (ptrmap[current_position.x - 1 + MAZE_WIDTH]
                [current_position.y + MAZE_HEIGHT] == NULL)){
            maze western_node = create_node();
            printf("Adding western node...\n");
            current_node->west = western_node;
            western_node->east = current_node;
            ptrmap[current_position.x - 1 + MAZE_WIDTH]
                    [current_position.y + MAZE_HEIGHT] = western_node;
        }
    }
    current_node->visited = true;
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

struct node *create_node(){
    printf("Adding new node...\n");
    struct node *new_node;
    new_node = malloc(sizeof(struct node));
    printf("Added new node!\n");
    new_node->visited = 0;
    new_node->north = NULL;
    new_node->east = NULL;
    new_node->west = NULL;
    new_node->south = NULL;
    new_node->position.x = 0;
    new_node->position.y = 0;
    return new_node;
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

void print_ptrmap(){
    int i, j;
    for(i = 0; i < 2 * MAZE_HEIGHT + 2; i++){
        for(j = 0; j < 2* MAZE_WIDTH + 2; j++) {
            if (ptrmap[i][j] != NULL) {
                printf(" 1");
            } else {
                printf(" 0");
            }
        }
        printf("\n");
    }
}

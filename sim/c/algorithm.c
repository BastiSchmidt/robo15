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


//Discover surrounding connected nodes and create them in map
void discover(){

    if (!current_node->visited){
        int new_intersection = 0;
        new_intersection = scan();

        //legacy map
        matrix[current_position.y + MAZE_HEIGHT][current_position.x + MAZE_WIDTH][0] =
                new_intersection;

        //go through all possible directions, look if there are undiscovered
        // nodes nearby
        if (direction_detect(new_intersection,NORTH)
                && (ptrmap[current_position.x + MAZE_WIDTH]
                [current_position.y + 1 + MAZE_HEIGHT] == NULL) ){
            maze northern_node = create_node();
            printf("Adding northern node...\n");

            //set up pointers of current and new node, fill in new nodes position
            current_node->north = northern_node;
            northern_node->south = current_node;
            northern_node->position.x = current_position.x;
            northern_node->position.y = current_position.y + 1;

            //update ptrmap with new node
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
            eastern_node->position.x = current_position.x + 1;
            eastern_node->position.y = current_position.y;

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
            southern_node->position.x = current_position.x;
            southern_node->position.y = current_position.y - 1;

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
            western_node->position.x = current_position.x - 1;
            western_node->position.y = current_position.y;

            ptrmap[current_position.x - 1 + MAZE_WIDTH]
                    [current_position.y + MAZE_HEIGHT] = western_node;
        }
        current_node->visited = 1; //current node is explored
    }
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

//return pointer to new, empty node
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

//appends the list the given pointer is pointing to with the given coord
void list_append(struct element **start, struct coord discovered) {

    struct element *iter = *start;

    if (iter == NULL) {
        iter = malloc(sizeof(struct element));
        iter->node_position = discovered;
        iter->next = NULL;
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

//remove the first entry of a list and update the pointer the dp is pointing to
void list_remove_first(struct element **start) {

    struct element *temp;

    if (*start == NULL) {
        return;
    }
    temp = *start;
    *start = temp->next;
    free(temp);
}


//completely free the list the given dp is pointing to
void destroy_list(struct element **start){
    if (start == NULL) return;
    if (*start == NULL) return;
    struct element *current = *start;
    struct element *iter = current->next;
    free(current);
    destroy_list(&(iter));
}

//outputs ptrmap to stdout, 1's show present pointers
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


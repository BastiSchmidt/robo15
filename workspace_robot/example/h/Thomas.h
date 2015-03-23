/*
 * Thomas.h
 *
 *  Created on: 17.03.2015
 *      Author: Thomas
 */

#ifndef H_THOMAS_H_
#define H_THOMAS_H_
int black;
int dreh;
#include <stdlib.h>
#include "kernel.h"
/* Will be generated: */
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "../src/Thomas.c"



//// Algo kram


void list_append(struct element **start, struct coord discovered);

void list_remove_first(struct element **start);

void destroy_list(struct element *start);

int list_search(struct element *start, struct coord tofind);

void reset_nodes_bfs();

void init();

void discover();

int direction_detect(int given_intersection, int wanted_direction);

int turn_d(int direction);

struct node *create_node();

struct coord bfs_closest_unvisited_node();

struct instructions bfs_path_to_node(struct coord goal);

struct coord shift_coordinates(struct coord old, int direction);

struct instructions create_path(struct coord goal_position);

int follow_instructions(struct instructions instr);
int main_loop();

//Current orientation of bot
int orientation;



///

void wait_ms(int ms);   /// Hilfsfunktionen
int sgn(float x);

void kalibrieren_drehen();  /// Kalibrierungsfunktionen
void kalibrieren_farbe();

void drehen_grad_r(int grad);
void drehen_grad_l(int grad);			/// Grundlegende Bewegungsfunktionen
void drive_cm(float cm);


int turn_left();                       /// Funktionen, die vom algo benötigt werden.
int turn_right();

void Token_found();						/// Token Funkionen
int check_Token();


void go_straigth();
void kalibrieren_Knoten();
void drive_cm2(float cm);
void printnumber(int zahl , int x, int y);


void follow_line();

int checkline_right (int steps, int drehung, int waittime);
int checkline_left (int steps, int drehung, int waittime);

int checkline(int Winkel,int Iterationen);

int forward();						/// erweiterte Bewegungsfunktionen
int goto_Node_center();
void Node_center_case1();
void Node_center_case2();

int get_Hits(int MAX_grad,int Position);
int scan();

#endif /* H_THOMAS_H_ */

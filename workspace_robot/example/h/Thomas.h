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




void follow_line();

int checkline_right (int steps, int drehung, int waittime);
int checkline_left (int steps, int drehung, int waittime);

int checkline(int Winkel,int Iterationen);

int forward();						/// erweiterte Bewegungsfunktionen
int goto_Node_center();
void Node_center_case1();
void Node_center_case2();

int get_Hits(int MAX_grad,int Position);
void scan_Node();
void scanNode(int orientation);		/// in entwicklung

#endif /* H_THOMAS_H_ */

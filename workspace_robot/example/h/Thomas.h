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


void step_left(int time);
void step_left(int time);
int steps_left(int steps, int steplenght);  /// veraltete / nicht gebrauchte Funktionen
int steps_right(int steps, int steplenght);
int FindLine(int old_Light);

int checkline_right (int steps, int drehung, int waittime);
int checkline_left (int steps, int drehung, int waittime);
int checkline(int Iterationen);
int forward();						/// erweiterte Bewegungsfunktionen
void goto_Node_center();

int get_Hits(int MAX_grad,int Position);
void scan_Node();
void scanNode(int orientation);		/// in entwicklung

void TEST();				/// Testfunktionen
void Linienfolgen_und_Knoten_finden();

#endif /* H_THOMAS_H_ */

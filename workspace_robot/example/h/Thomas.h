/*
 * Thomas.h
 *
 *  Created on: 17.03.2015
 *      Author: Thomas
 */

#ifndef H_THOMAS_H_
#define H_THOMAS_H_

#include <stdlib.h>
#include "kernel.h"
/* Will be generated: */
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "../src/Thomas.c"



void wait_ms(int ms);
int sgn(float x);

void drehen_grad_r(int grad);
void drehen_grad_l(int grad);
void drehen();

void scanNode(int orientation);

void drive_cm(float cm);
void drive(int umdr);

void step_left(int time);
void step_left(int time);

int steps_left(int steps, int steplenght);
int steps_right(int steps, int steplenght);

int FindLine(int old_Light);

void checkline(int SCHWARZ);
void Get_Black_White();


#endif /* H_THOMAS_H_ */

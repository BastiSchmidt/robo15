/*
 * david.h
 *
 *  Created on: 17.03.2015
 *      Author: David
 */

#ifndef H_DAVID_H_
#define H_DAVID_H_
#include "../src/david.c"


void drehen_grad_r(int grad);
void drehen_grad_l(int grad);
void wait_ms(int ms);
void scanNode(int orientation);
void drive(int umdr);

#endif /* H_DAVID_H_ */

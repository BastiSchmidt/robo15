/*
 * Thomas.c
 *
 *  Created on: 17.03.2015
 *      Author: Thomas
 */


#include "../h/Thomas.h"


void checkline()
{
	int Light = ecrobot_get_light_sensor(NXT_PORT_S3);
	while (Light<500)
	{
		Light = ecrobot_get_light_sensor(NXT_PORT_S3);
		nxt_motor_set_speed(NXT_PORT_B,100,0);
		systick_wait_ms(10);
		nxt_motor_set_speed(NXT_PORT_B,0,0);
		systick_wait_ms(1000);
	}
}
void drive()
{
	nxt_motor_set_speed(NXT_PORT_B,100,0);
	nxt_motor_set_speed(NXT_PORT_C,100,0);
	systick_wait_ms(50);
	nxt_motor_set_speed(NXT_PORT_B,0,0);
	nxt_motor_set_speed(NXT_PORT_C,0,0);
}


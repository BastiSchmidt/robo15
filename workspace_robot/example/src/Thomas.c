#include "../h/Thomas.h"


void wait_ms(int ms){
	 int time =systick_get_ms();
	 while( systick_get_ms()> time + ms)
	 {
	 }
}

void drehen_grad_r(int grad){

	float umdr = (grad * 8/3) - 5;// 1°drehen entspricht 2.66° Raddrehen, 10 grad weniger wg. Traegheit
	int power = 75; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C , power , 0);
		nxt_motor_set_speed(NXT_PORT_B , -power , 0);
		wait_ms(60);
		nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//		if(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat
//			                                                                 // und dann entsprehend angleichen
//		{
//			while(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
//			{
//				nxt_motor_set_speed(NXT_PORT_C , power , 0);
//				wait_ms(20);
//				nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//			}
//		}
//		else
//		{
//			while(nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
//			{
//				nxt_motor_set_speed(NXT_PORT_B , power , 0);
//				wait_ms(100);
//				nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//			}
//		}
	}
}

void drehen_grad_l(int grad)
{

	float umdr = (grad * 8/3) ;// 1°drehen entspricht 2.66° Raddrehen, 10 grad weniger wg. Trägheit
	int power = 75; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C , -power , 0);
		nxt_motor_set_speed(NXT_PORT_B , power , 0);
		wait_ms(100);
		nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//		if(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat
//			                                                                 // und dann entsprehend angleichen
//		{
//			while(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
//			{
//				nxt_motor_set_speed(NXT_PORT_C , power , 0);
//				wait_ms(20);
//				nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//			}
//		}
//		else
//		{
//			while(nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
//			{
//				nxt_motor_set_speed(NXT_PORT_B , power , 0);
//				wait_ms(100);
//				nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//			}
//		}
	}
}
void drehen()
{
	int umdr = 950;// 360 grad drehen bei ca.950 grad Raddrehen
	int power = 75; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C , power , 0);
		nxt_motor_set_speed(NXT_PORT_B , -power , 0);
		wait_ms(50);
		nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//		if(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat
//			                                                                 // und dann entsprehend angleichen
//		{
//			while(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
//			{
//				nxt_motor_set_speed(NXT_PORT_C , power , 0);
//				wait_ms(20);
//				nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//			}
//		}
//		else
//		{
//			while(nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
//			{
//				nxt_motor_set_speed(NXT_PORT_B , power , 0);
//				wait_ms(100);
//				nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//			}
//		}
	}
	wait_ms(6000);
}

void drive(int umdr)
{
	int power = 60; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C , power , 0);
		nxt_motor_set_speed(NXT_PORT_B , power , 0);
		wait_ms(100);
		nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
		if(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat
			                                                                 // und dann entsprehend angleichen
		{
			while(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
			{
				nxt_motor_set_speed(NXT_PORT_C , power , 0);
				wait_ms(20);
				nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
			}
		}
		else
		{
			while(nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
			{
				nxt_motor_set_speed(NXT_PORT_B , power , 0);
				wait_ms(100);
				nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
			}
		}
	}

}


void step_left(int time)
{
	nxt_motor_set_speed(NXT_PORT_B,100,0);
	nxt_motor_set_speed(NXT_PORT_C,-100,0);
	systick_wait_ms(time);
	nxt_motor_set_speed(NXT_PORT_B,0,0);
	nxt_motor_set_speed(NXT_PORT_C,0,0);
}
void step_right(int time)
{
	nxt_motor_set_speed(NXT_PORT_C,100,0);
	nxt_motor_set_speed(NXT_PORT_B,-100,0);
	systick_wait_ms(time);
	nxt_motor_set_speed(NXT_PORT_C,0,0);
	nxt_motor_set_speed(NXT_PORT_B,0,0);
}
int steps_left(int steps, int steplenght)
{
	int i;
	for (i=0;i<steps;i++)
	{
		int Light = ecrobot_get_light_sensor(NXT_PORT_S3);
		if (Light>500)
		{
			return 1;  /// Roboter hat eine Schwarze Linie gefunden ---> brich drehen ab!!
		}
		drehen_grad_l(steplenght);


	}
	return 0;  /// Roboter hat keine Schwarze Linie gefunden
}
void checkline()
{
	int Line = 0;
	while (Line!=1)  /// Wiederhole, solange Schwarze Linie nicht gefunden
	{
		Line = steps_left(5,5); /// Drehe links
	}
}

<<<<<<< HEAD
=======
//void drive()
//{
//	nxt_motor_set_speed(NXT_PORT_B,100,0);
//	nxt_motor_set_speed(NXT_PORT_C,100,0);
//	systick_wait_ms(50);
//	nxt_motor_set_speed(NXT_PORT_B,0,0);
//	nxt_motor_set_speed(NXT_PORT_C,0,0);
//}
int sgn(float x)
{
	if(x>=0)
	{
		return 1;
	}
	else
	{
		return -1;
	}

}

void drive_cm(float cm)
{

	float umdr =sgn(cm) *cm * 2000/97;
	int power = sgn(cm)* 95; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C , power , 0);
		nxt_motor_set_speed(NXT_PORT_B , power , 0);
		wait_ms(100);
		nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//		if(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat
//			                                                                 // und dann entsprehend angleichen
//		{
//			while(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
//			{
//				nxt_motor_set_speed(NXT_PORT_C , power , 0);
//				wait_ms(20);
//				nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//			}
//		}
//		else
//		{
//			while(nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
//			{
//				nxt_motor_set_speed(NXT_PORT_B , power , 0);
//				wait_ms(100);
//				nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//			}
//		}
	}
}


void scanNode(int orientation)
{


				 // erstens: finden des der gegenüberliegenden Linie.
	             // dann 1cm weiterfahren, um weitere abgehende Linien zu finden
	drive_cm(1);
	drehen_grad_l(10);//erst mal 10 grad drehen für anfang
	// jetzt drehen und linien suchen:
	// drehen um 80 grad, 15 grad gucken, etc.
	//drehen_grad_l(90);
	for(int i =1; i<4;i++)
	{
		int Winkel = 0; //Zählt winkel mit
		drehen_grad_l(70)
		while(Winkel < 20) //winkel
		{
			drehen_grad_l(2);
			Winkel +=2;
			if(ecrobot_get_light_sensor(NXT_PORT_S3)<500)
		}
	}

	int light = ecrobot_get_light_sensor(NXT_PORT_S3);


}
>>>>>>> origin/master

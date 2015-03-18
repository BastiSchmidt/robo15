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
int FindLine(int old_Light);
int steps_left(int steps, int steplenght)
{
	int i,a,Light;
	for (i=0;i<steps;i++)
	{
		Light = ecrobot_get_light_sensor(NXT_PORT_S3);
		drehen_grad_l(steplenght);
		a = FindLine(Light);
		if (a==1)
		{
			return 1; /// Roboter hat die Schwarze Linie gefunden
		}
		if (FindLine(Light)==1)
		{
			/// genauere Suche??? Später TODO
		}


	}
	return 0;  /// Roboter hat keine Schwarze Linie gefunden
}

int steps_right(int steps, int steplenght)
{
	int i,a,Light;
	for (i=0;i<steps;i++)
	{
		Light = ecrobot_get_light_sensor(NXT_PORT_S3);
		drehen_grad_r(steplenght);
		a = FindLine(Light);
		if (a==1)
		{
			return 1; /// Roboter hat die Schwarze Linie gefunden
		}
		if (FindLine(Light)==1)
				{
					/// genauere Suche??? Später TODO
				}


	}
	return 0;  /// Roboter hat keine Schwarze Linie gefunden
}


void checkline(int SCHWARZ)
{
	int i,j;
	int waittime = 5;
	int drehung = 10;
	int Anzahl = 3;
	i=0;
	j=1;
	while (1)
	{

		for (i=0;i<Anzahl*j;i++)
				{
					if (ecrobot_get_light_sensor(NXT_PORT_S3)>SCHWARZ)
					{
//						ecrobot_sound_tone(1000, 500, 10);
						return;
					}
					drehen_grad_r(drehung);
					systick_wait_ms(waittime);
				}
		for (i=0;i<Anzahl*j;i++)
		{

			if (ecrobot_get_light_sensor(NXT_PORT_S3)>SCHWARZ)
			{
//				ecrobot_sound_tone(1000, 500, 10);
				return;
			}
			drehen_grad_l(drehung);
			systick_wait_ms(waittime);
		}
		for (i=0;i<Anzahl*j;i++)
		{
			if (ecrobot_get_light_sensor(NXT_PORT_S3)>SCHWARZ)
			{
//				ecrobot_sound_tone(1000, 500, 10);
				return;
			}
			drehen_grad_l(drehung);
			systick_wait_ms(waittime);
		}
		for (i=0;i<Anzahl*j;i++)
		{
			if (ecrobot_get_light_sensor(NXT_PORT_S3)>SCHWARZ)
			{
//				ecrobot_sound_tone(1000, 500, 10);
				return;
			}
			drehen_grad_r(drehung);
			systick_wait_ms(waittime);
		}
		j++;
	}
}

int FindLine(int old_Light)  /// returns 0 if nothing happens -1, if black-->white, 1 if white -> black
{
//	ecrobot_sound_tone(1000, 2000, 10);
	systick_wait_ms(500);
	int new_Light = ecrobot_get_light_sensor(NXT_PORT_S3);
	int Diff = new_Light - old_Light;
	if (abs(Diff) > 50)
	{

		if (Diff>0)  /// Dunkel auf Hell
		{
//			systick_wait_ms(1050);
//			ecrobot_sound_tone(1000, 1000, 10);
//			systick_wait_ms(1050);
			return -1;

		}
		else  /// Hell auf Dunkel
		{

//			systick_wait_ms(1050);
//			ecrobot_sound_tone(1000, 1000, 10);
//			systick_wait_ms(1050);
//			ecrobot_sound_tone(1000, 1000, 10);
//			systick_wait_ms(1050);
			return 1;

		}


	}
//	systick_wait_ms(1050);
//	ecrobot_sound_tone(1000, 1000, 10);
//	systick_wait_ms(1050);
//	ecrobot_sound_tone(1000, 1000, 10);
//	systick_wait_ms(1050);
//	ecrobot_sound_tone(1000, 1000, 10);
//	systick_wait_ms(1050);
	return 0;
}

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


//void scanNode(int orientation)
//{
//
//
//				 // erstens: finden des der gegenüberliegenden Linie.
//	             // dann 1cm weiterfahren, um weitere abgehende Linien zu finden
//	drive_cm(1);
//	drehen_grad_l(10);//erst mal 10 grad drehen für anfang
//	// jetzt drehen und linien suchen:
//	// drehen um 80 grad, 15 grad gucken, etc.
//	//drehen_grad_l(90);
//	for(int i =1; i<4;i++)
//	{
//		int Winkel = 0; //Zählt winkel mit
//		drehen_grad_l(70);
//		while(Winkel < 20) //winkel
//		{
//			drehen_grad_l(2);
//			Winkel +=2;
//			if(ecrobot_get_light_sensor(NXT_PORT_S3)<500)
//		}
//	}
//
//	int light = ecrobot_get_light_sensor(NXT_PORT_S3);





#include "../h/Thomas.h"


int black = 500;
int dreh = 1030;
void wait_ms(int ms){
	 int time =systick_get_ms();
	 while( systick_get_ms()> time + ms)
	 {
	 }
}

void drehen_grad_r(int grad)
{
	// Drehung wird unabhängig von richtung gezählt!!

	float umdr = (grad * dreh/360) ;// 1°drehen entspricht 2.66° Raddrehen, 10 grad weniger wg. Trägheit
	int power = 90; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C ,  power , 0);
		nxt_motor_set_speed(NXT_PORT_B , -power , 0);
		wait_ms(10);

	}
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//	if(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat
//		                                                                 // und dann entsprehend angleichen
//	{
//		while(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
//		{
//			nxt_motor_set_speed(NXT_PORT_C , -power , 0);
//			wait_ms(50);
//			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//		}
//	}
//	else
//	{
//		while(nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
//		{
//			nxt_motor_set_speed(NXT_PORT_B , power , 0);
//			wait_ms(50);
//			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//		}
//	}

}

void drehen_grad_l(int grad)
{
	// Drehung wird unabhängig von richtung gezählt!!

	float umdr = (grad * dreh/360) ;// 1°drehen entspricht 2.66° Raddrehen, 10 grad weniger wg. Trägheit
	int power = 80; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C ,-power , 0);
		nxt_motor_set_speed(NXT_PORT_B , power , 0);
		wait_ms(10);

	}
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//	if(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat
//		                                                                 // und dann entsprehend angleichen
//	{
//		while(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
//		{
//			nxt_motor_set_speed(NXT_PORT_C , -power , 0);
//			wait_ms(50);
//			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//		}
//	}
//	else
//	{
//		while(nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
//		{
//			nxt_motor_set_speed(NXT_PORT_B , power , 0);
//			wait_ms(50);
//			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//		}
//	}

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
		drehen_grad_l(i);

	}
	return 0;  /// Roboter hat keine Schwarze Linie gefunden
}
void checkline()
{
	int f,Line = 0;
	int j = 1;
	while (Line!=1)
	{
		Line = steps_left(1,25);
	}
}

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
	int gradeaus =0;
	int links =0;
	int rechts =0;
	// 1
//	int lvar=0;
//	int rvar=0;
//	int steps;
//	int time = 100;
//	while(ecrobot_get_light_sensor(NXT_PORT_S3)<500)//weiß. gute abbruchbed, aber in schleife wird dann schwarz detektiert. DANN ABBR.
//	{
//
//		drive_cm(1);// fahren
////		// getz gucken
//		//links
//		while(lvar<10 && ecrobot_get_light_sensor(NXT_PORT_S3)<500)
//		{
//			step_left(time);
//			lvar++;
//		}//10 schritte nach rechts gegangen oder auf schwarz getroffen
//		if(lvar==10)
//		{// zurück auf anfang, links war nüscht.
//			for(int i=0;i<10;i++)
//			{
//				step_right(time);
//
//			}
//			lvar=0;
//		}
//		else// et fiat nox
//		{
//			drive_cm(3);
//		}
//  }
	//2
	if (ecrobot_get_light_sensor(NXT_PORT_S3)>500)
	{
		gradeaus=1;
	}
	// jetzt drehen und linien suchen:
	int Winkel = 0; //Zählt winkel mit
	while(Winkel < 360 )
	{

		drehen_grad_l(5);
		Winkel +=5;
		wait_ms(500);
		if(ecrobot_get_light_sensor(NXT_PORT_S3)>300)// Licht: größer als 500: Schwarz
		{
			ecrobot_sound_tone(300, 500, 30);// für test
//			if(Winkel > 80 && Winkel<100){rechts =1;}
//			if(Winkel > 260 && Winkel<280){links = 1;}
			// gefunden: Linie im algo updaten, trotzdem weiterdrehen, um winkel beizubehalten.
		}		if(ecrobot_get_light_sensor(NXT_PORT_S3)>500)// Licht: größer als 500: Schwarz
		{
			ecrobot_sound_tone(600, 500, 30);// für test
//			if(Winkel > 80 && Winkel<100){rechts =1;}
//			if(Winkel > 260 && Winkel<280){links = 1;}
			// gefunden: Linie im algo updaten, trotzdem weiterdrehen, um winkel beizubehalten.
		}		if(ecrobot_get_light_sensor(NXT_PORT_S3)>600)// Licht: größer als 500: Schwarz
		{
			ecrobot_sound_tone(1200, 500, 30);// für test
//			if(Winkel > 80 && Winkel<100){rechts =1;}
//			if(Winkel > 260 && Winkel<280){links = 1;}
			// gefunden: Linie im algo updaten, trotzdem weiterdrehen, um winkel beizubehalten.
		}
	}
	ecrobot_sound_tone(880, 500, 30);
	// winkel gecheckt	// string bauen
	display_clear(0);
	char str1[12] = "LINKS ";
	char str2[12] = "RECHTS ";
	char str3[12] = "GRADEAUS";
	if(links)
	{
		display_goto_xy(1,1);
		display_string(str1);
	}
	if(rechts)
	{
		display_goto_xy(2,1);
		display_string(str2);
	}
	if(gradeaus)
	{
		display_goto_xy(3,1);
		display_string(str3);
	}
	// ergebnis berechnen und zurückgeben
}

/*		display_clear(0);
		char str3[12] = "GRADEAUS";
		display_goto_xy(5,2);
		display_string(str3);
 *
 *
 *
 */
/*
 * Start auf Schwarz, dreht sich einmal
 * kalibriert dadurch lichtsensor und drehungszahl
 */
void kalibrieren_drehen()
{
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int umdr = 900;
	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)
	{
		nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
		nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
		wait_ms(50);
	}// bissel gedreht, jetzt Schwarz suchen
	while(ecrobot_get_light_sensor(NXT_PORT_S3)<black)
	{
		nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
		nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
		wait_ms(40);
	}// jetzt issa auf schwarz. Motoren aus
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
	//wait_ms(100);// evtl. nochma gucken, ob wa immanoch uff schwarz sind
	//jetzt drehungen vergleichen und dreh berechnen
	int b = nxt_motor_get_count(NXT_PORT_B);
	int c = nxt_motor_get_count(NXT_PORT_C);
	if(b<c+30 && c<b+30)
	{
		display_clear(0);
		char str3[12] = "Wunderbar";
		display_goto_xy(1,2);
		display_string(str3);
		char str4[12] = "Kalibriert";
		display_goto_xy(1,4);
		display_string(str4);
	}
	else
	{
		display_clear(0);
		char str3[12] = "err";
		display_goto_xy(1,2);
		display_string(str3);
		if(b<c)
		{

		}
		else
		{

		}
	}
}

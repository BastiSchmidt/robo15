#include "../h/Thomas.h"


int black;  /// MAXIMALES SCHWARZ minus Toleranz siehe: Get_Black_White
int white;  /// MININMALES WEIß plus Toleranz
int Toleranz = 100;
int dreh = 1030;

void wait_ms(int ms)
{
	 int time =systick_get_ms();
	 while( systick_get_ms()> time + ms)
	 {
	 }
}

void drehen_grad_r(int grad)
{

	float umdr = (grad * dreh/360) ;// 1°drehen entspricht 2.66° Raddrehen, 10 grad weniger wg. Trägheit
	int power = 90; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

	while(nxt_motor_get_count(NXT_PORT_B)< umdr && -nxt_motor_get_count(NXT_PORT_C)< umdr)
	{
		nxt_motor_set_speed(NXT_PORT_C , -80 , 0);
		nxt_motor_set_speed(NXT_PORT_B , 80 , 0);
		wait_ms(50);
		if(nxt_motor_get_count(NXT_PORT_B) > -nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
		{
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
			while(nxt_motor_get_count(NXT_PORT_B) > -nxt_motor_get_count(NXT_PORT_C))
			{
				nxt_motor_set_speed(NXT_PORT_C ,-80 , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		}
		if(nxt_motor_get_count(NXT_PORT_B) < -nxt_motor_get_count(NXT_PORT_C))
		{
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
			while(-nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
			{
				nxt_motor_set_speed(NXT_PORT_B , 80 , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
		}
	}

}

void drehen_grad_l(int grad)
{
	// Drehung wird unabhängig von richtung gezählt!!


	float umdr = (grad * dreh/360) ;// 1°drehen entspricht 2.66° Raddrehen, 10 grad weniger wg. Trägheit
	int power = 80; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

	while(-nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)
	{
		nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
		nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
		wait_ms(50);
		if(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
		{
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
			while(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
			{
				nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		}
		if(-nxt_motor_get_count(NXT_PORT_B) < nxt_motor_get_count(NXT_PORT_C))
		{
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
			while(nxt_motor_get_count(NXT_PORT_C) > -nxt_motor_get_count(NXT_PORT_B))
			{
				nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
		}
	}

}
void drehen()
{
	int umdr = 950;// 360 grad drehen bei ca.950 grad Raddrehen
	int power = 75; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

	while(-nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)
	{
		nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
		nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
		wait_ms(50);
		if(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
		{
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
			while(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
			{
				nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		}
		if(-nxt_motor_get_count(NXT_PORT_B) < nxt_motor_get_count(NXT_PORT_C))
		{
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
			while(nxt_motor_get_count(NXT_PORT_C) > -nxt_motor_get_count(NXT_PORT_B))
			{
				nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
		}
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

/// TODO Schleifen entfernen, damit Knoten erkannt werden können
/// erst jedoch sensor weiter nach vorne sezten
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

void Get_Black_White()
{
	int i,Light;
	int MAX_BLACK = 0;
	int MIN_WHITE = 1023;


	for (i=0;i<=360;i+=5) /// Muss sich ~ 360° Drehen
		{
			Light = ecrobot_get_light_sensor(NXT_PORT_S3);
			if (Light>MAX_BLACK)
			{
				MAX_BLACK = Light;
			}
			if (Light<MIN_WHITE)
					{
				MIN_WHITE = Light;
					}
			drehen_grad_l(5);
			wait_ms(20);


		}
	white = MIN_WHITE + Toleranz;
	black = MAX_BLACK - Toleranz;
	checkline(black-300);
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
	black = ecrobot_get_light_sensor(NXT_PORT_S3)-50; //falls noch nicht kalibriert
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int umdr = 900;

	while(-nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)
	{
		nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
		nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
		wait_ms(50);
		if(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
		{
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
			while(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
			{
				nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		}
		if(-nxt_motor_get_count(NXT_PORT_B) < nxt_motor_get_count(NXT_PORT_C))
		{
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
			while(nxt_motor_get_count(NXT_PORT_C) > -nxt_motor_get_count(NXT_PORT_B))
			{
				nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
		}
	}// bissel gedreht, jetzt Schwarz suchen
	while(ecrobot_get_light_sensor(NXT_PORT_S3)<=black)
	{
		nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
		nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
		wait_ms(20);
		if(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
		{
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
			while(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
			{
				nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		}
		if(-nxt_motor_get_count(NXT_PORT_B) < nxt_motor_get_count(NXT_PORT_C))
		{
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
			while(nxt_motor_get_count(NXT_PORT_C) > -nxt_motor_get_count(NXT_PORT_B))
			{
				nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
		}
	}// jetzt issa auf schwarz. Motoren aus
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
	//wait_ms(100);// evtl. nochma gucken, ob wa immanoch uff schwarz sind
	//jetzt drehungen vergleichen und dreh berechnen
	int b = nxt_motor_get_count(NXT_PORT_B);
	int c = nxt_motor_get_count(NXT_PORT_C);
	ecrobot_sound_tone(200, 500, 30);// für test
	wait_ms(100);
	ecrobot_status_monitor("Hello, wuff");
	if(-b==c || (b<c+10 && c<b+10) )
	{
		display_clear(0);
		char str3[12] = "Kalibriert";
		display_goto_xy(5, 2);
		display_string(str3);
		display_goto_xy(1,3);
		display_int(-b-c, 6);
		wait_ms(500);
		dreh = b;

	}
	else
	{
		display_clear(0);
		char str3[12] = "Wuff Error";
		display_goto_xy(5, 2);
		display_string(str3);
		display_goto_xy(1,3);
		display_int(b, 6);
		display_goto_xy(1,4);
		display_int(c, 6);
		systick_wait_ms(2000);
		ecrobot_sound_tone(800, 500, 30);// für test
	}
}


void TEST ()
{
	ecrobot_sound_tone(1000, 1000, 10);
		systick_wait_ms(5000);
		ecrobot_sound_tone(1000, 1000, 10);
		display_clear(1);
		display_goto_xy(1,0);
		display_int(white,5);
		systick_wait_ms(5000);
		ecrobot_sound_tone(1000, 1000, 10);
		systick_wait_ms(5000);
		ecrobot_sound_tone(1000, 1000, 10);
		display_clear(1);
		display_goto_xy(1,0);
		display_int(black,5);
		while (1)
		{

		}
}


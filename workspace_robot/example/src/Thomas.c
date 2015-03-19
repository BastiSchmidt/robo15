#include "../h/Thomas.h"


int black;  /// MAXIMALES SCHWARZ minus Toleranz siehe: Get_Black_White
int white;  /// MININMALES WEIß plus Toleranz
float Toleranz_black = 0.6;
float Toleranz_white = 0.25;
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

	/// Korrektur von Thomas
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	// das hier ist wichtig, denn falls im letzten Schritt
	///der While Schleife beide nxt_motor_get_count den EXAKT selben Wert ausgeben wird keine der
	///beiden if bedingungen erfüllt und die Motoren werden nicht ausgeschaltet!!!
	///
}

void drehen_grad_l(int grad)
{

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

	/// Korrektur von Thomas
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	// das hier ist wichtig, denn falls im letzten Schritt
	///der While Schleife beide nxt_motor_get_count den EXAKT selben Wert ausgeben wird keine der
	///beiden if bedingungen erfüllt und die Motoren werden nicht ausgeschaltet!!!
	///

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
	int power = 95; //Prozentzahl für Motoren
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


int checkline(int Iterationen)
{

	/// CHECKLINE GEHT DAVON AUS, DASS MAN SICH AUF WEIß BEFINDET
	/// IST MAN AUF SCHWARZ, KANN ES SEIN DASS ER SCHWARZ FÄLSCHLICHERWEISE ALS WEIß ERKENNT

	int i,j;
	int waittime = 5;
	int drehung = 5;
	int Anzahl = 3;
	i=0;
	j=1;
	while (j<Iterationen+1) // 2 Iterationen
	{

		for (i=0;i<Anzahl*j;i++)
		{
			if (ecrobot_get_light_sensor(NXT_PORT_S3)>black)
			{
//				ecrobot_sound_tone(1000, 500, 10);
				return 1;
			}
			drehen_grad_r(drehung);
			systick_wait_ms(waittime);
		}
		for (i=0;i<Anzahl*j;i++)
		{

			if (ecrobot_get_light_sensor(NXT_PORT_S3)>black)
			{
//				ecrobot_sound_tone(500, 500, 10);
				return 1;
			}
			drehen_grad_l(drehung);
			systick_wait_ms(waittime);
		}
		/// systick_wait_ms(1000);
		for (i=0;i<Anzahl*j;i++)
		{
			if (ecrobot_get_light_sensor(NXT_PORT_S3)>black)
			{
//				ecrobot_sound_tone(500, 500, 10);
				return 1;
			}
			drehen_grad_l(drehung);
			systick_wait_ms(waittime);
		}
		for (i=0;i<Anzahl*j;i++)
		{
			if (ecrobot_get_light_sensor(NXT_PORT_S3)>black)
			{
//				ecrobot_sound_tone(500, 500, 10);
				return 1;
			}
			drehen_grad_r(drehung);
			systick_wait_ms(waittime);
		}
		j++;
	}
	ecrobot_sound_tone(100, 2000, 10);
	return 0;
}
void drive_cm(float cm);
int forward() /// returns 1 if still on Black returns 0 if it left black and is on white

/// FORWARD GEHT DAVON AUS, DASS MAN SICH AUF SCHWARZ BEFINDET
/// IST MAN AUF WEIß, KANN ES SEIN DASS ER WEIß FÄLSCHLICHERWEISE ALS SCHWARZ ERKENNT UND WEITERFÄHRT

{
	int i;
	int waittime = 20;
	float Strecke = 2;
	for (i=0;i<10;i++)
	{
		if (ecrobot_get_light_sensor(NXT_PORT_S3)<white) /// ist es sehr weiß hier?
		{
			return 0;
		}
		drive_cm(Strecke);
		systick_wait_ms(waittime);

	}
	return 1;

}

void follow_line() /// follow_line fährt bis zum nächsten Knoten
{
	/// FOLLOW-LINE GEHT DAVON AUS, DASS MAN AUF SCHWARZ IST
	int Light = 1; /// 1 bedeutet Schwarz
	while(Light == 1)
	{
		while(Light == 1)
		{
			Light = forward();
		}
		Light = checkline(3);
	}
}
void goto_Node_center()
{
	drive_cm(12);
	drehen_grad_l(360);
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

void kalibrieren_farbe()
{
	int i,Light;
	int No_Line_Found=0;
	int MAX_BLACK = 0;
	int MIN_WHITE = 1023;


	for (i=0;i<=360;i+=5)
		{
			Light = ecrobot_get_light_sensor(NXT_PORT_S3);
			if (Light>MAX_BLACK)
			{
				MAX_BLACK = Light; /// Aktualisiere höchsten Black wert
			}
			if (Light<MIN_WHITE)
					{
				MIN_WHITE = Light; /// Aktualisiere niedrigsten White wert
					}

			drehen_grad_r(5); /// Dreh dich! ~360°
			wait_ms(20);


		}

	white = MIN_WHITE + (MAX_BLACK - MIN_WHITE)*Toleranz_white;  /// DEFINIERE GLOBALE VARIABLEN UM
	black = MAX_BLACK - (MAX_BLACK - MIN_WHITE)*Toleranz_black;

//	display_clear(1);
//	char str1[12] = "whitexxxxxx";
//	display_goto_xy(5, 2);				/// Display Ausgabe
//	display_string(str1);
//
//	systick_wait_ms(3000);
//
//	display_clear(1);
//	display_goto_xy(1,0);
//	display_int(white,5);
//
//	systick_wait_ms(3000);
//
//	display_clear(1);
//	char str2[12] = "blackxxxxxx";
//	display_goto_xy(5, 2);				/// Display Ausgabe
//	display_string(str2);
//
//	systick_wait_ms(3000);
//
//	display_clear(1);
//	display_goto_xy(1,0);
//	display_int(black,5);
//
//	systick_wait_ms(3000);
//	ecrobot_sound_tone(500, 1000, 10);
//	systick_wait_ms(1050);				/// Akustische Ausgabe
//
//
//	display_clear(1);
//	char str3[12] = "Kalibriert";
//	display_goto_xy(5, 2);				/// Display Ausgabe
//	display_string(str3);



	No_Line_Found = checkline(4); /// Zurück zur Linie

	systick_wait_ms(1050);
	ecrobot_sound_tone(300, 1000, 10);
	systick_wait_ms(1050);

	if (No_Line_Found == 0)
	{
		ecrobot_sound_tone(1000, 1000, 10);
		display_clear(1);
		char str4[14] = "LINIE VERLOREN";
		display_goto_xy(5, 2);				/// Display Ausgabe
		display_string(str4);
		while (1)
		{
			/// ABBRUCH
		}

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
	/// Änderung von Thomas : hab das unten mal auskommentiert, da sonst die erzeugte black variable überschrieben wird
	/// black = ecrobot_get_light_sensor(NXT_PORT_S3)-300; //falls noch nicht kalibriert
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
		dreh = -b; /// Korrektur von Thomas: hab aus b -b gemacht, weil dreh sonst negativ war.

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

void Linienfolgen_und_Knoten_finden()
{
	int i = 0;
	int On_the_Line = 1; /// 1 bedeutet Schwarz, d.h wir befinden uns zu beginn auf schwarz
	while (On_the_Line == 1)  /// Fahre solange, bis schwarz verlassen
	{
		On_the_Line = forward();
	}

	if (checkline(2)== 0)  /// versuche Schwarz wieder zu finden
	{
		while (i<5)
		{
			wait_ms(1000);
			i++;
			/// Roboter hat Knoten gefunden und bricht ab
		}
	}
}

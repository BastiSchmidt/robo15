#include "../h/Thomas.h"


int black;  /// MAXIMALES SCHWARZ minus Toleranz siehe: Get_Black_White
int white;  /// MININMALES WEIß plus Toleranz
float Toleranz_black = 0.7; /// Erfahrungswerte Anwendung siehe kalibrierung_farbe
float Toleranz_white = 0.2;
int dreh = 1030;  /// Gute Näherung, Kalibrierung in kalibrierung_drehen()

void wait_ms(int ms)  /// Diese Tolle Funktion lässt Zeit voranschreiten, ohne Motoren abzuschalten
{
	 int time =systick_get_ms();
	 while( systick_get_ms()> time + ms)
	 {
	 }
}

void Token_found()   /// Wird aufgerufen, wenn Token gefunden #noshit
{
	/// TODO erhöhe Token Variable um 1
	ecrobot_sound_tone(500, 2000, 10);
	systick_wait_ms(10000);
}

void drehen_grad_l(int grad)  /// dreht nach links
{

	float umdr = (grad * dreh/360) ;// 1°drehen entspricht 2.66° Raddrehen, 10 grad weniger wg. Trägheit
	int power = 80; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

	while(nxt_motor_get_count(NXT_PORT_B)< umdr && -nxt_motor_get_count(NXT_PORT_C)< umdr)
	{
		nxt_motor_set_speed(NXT_PORT_C , -power , 0);
		nxt_motor_set_speed(NXT_PORT_B , power , 0);
		wait_ms(50);
		if(nxt_motor_get_count(NXT_PORT_B) > -nxt_motor_get_count(NXT_PORT_C)) //kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
		{
			nxt_motor_set_speed(NXT_PORT_B ,power/2 ,0); // den, der zuviel hat ausmachen
			while(nxt_motor_get_count(NXT_PORT_B) > -nxt_motor_get_count(NXT_PORT_C))
			{
				nxt_motor_set_speed(NXT_PORT_C ,-power , 0);     // den anderen aufholen lassen
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);  //wieder ausmachen, alle Motoren sind aus
		}
		if(nxt_motor_get_count(NXT_PORT_B) < -nxt_motor_get_count(NXT_PORT_C)) // kucken ob der andere mehr umdrehugen hat
		{
			nxt_motor_set_speed(NXT_PORT_C , power/2,0); // den, der zuviel hat ausmachen
			while(-nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
			{
				nxt_motor_set_speed(NXT_PORT_B , power , 0); // den anderen aufholen lassen
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1); // wieder ausmachen, alle Motoren sind aus
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

void drehen_grad_r(int grad)
{

	float umdr = (grad * dreh/360) ;// 1°drehen entspricht 2.66° Raddrehen, 10 grad weniger wg. Trägheit
	int power = 80; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

	while(-nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)
	{
		nxt_motor_set_speed(NXT_PORT_C , power , 0);
		nxt_motor_set_speed(NXT_PORT_B , -power , 0);
		wait_ms(50);
		if(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
		{
			nxt_motor_set_speed(NXT_PORT_B , power/2,0);
			while(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
			{
				nxt_motor_set_speed(NXT_PORT_C , power , 0);
				wait_ms(10);

			}
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		}
		if(-nxt_motor_get_count(NXT_PORT_B) < nxt_motor_get_count(NXT_PORT_C))
		{
			nxt_motor_set_speed(NXT_PORT_C , power/2,0);
			while(nxt_motor_get_count(NXT_PORT_C) > -nxt_motor_get_count(NXT_PORT_B))
			{
				nxt_motor_set_speed(NXT_PORT_B , -power , 0);
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


int checkline_left (int steps, int drehung, int waittime)
{
	int i;
	for (i=0;i<steps;i++)
	{

		if (ecrobot_get_light_sensor(NXT_PORT_S3)>black)
		{
//				ecrobot_sound_tone(500, 500, 10);
			return 1;
		}
		drehen_grad_l(drehung);
		systick_wait_ms(waittime);
	}
	return 0;
	/// systick_wait_ms(1000);
}

int checkline_right (int steps, int drehung, int waittime)
{
	int i;
	for (i=0;i<steps;i++)
	{

		if (ecrobot_get_light_sensor(NXT_PORT_S3)>black)
		{
//				ecrobot_sound_tone(500, 500, 10);
			return 1;
		}
		drehen_grad_r(drehung);
		systick_wait_ms(waittime);
	}
	return 0;
	/// systick_wait_ms(1000);
}


int checkline(int Winkel,int Iterationen)
{

	/// CHECKLINE GEHT DAVON AUS, DASS MAN SICH AUF WEIß BEFINDET
	/// IST MAN AUF SCHWARZ, KANN ES SEIN DASS ER SCHWARZ FÄLSCHLICHERWEISE ALS WEIß ERKENNT

	int j =1;
	int waittime = 20;
	int drehung = 5;

	int step = (Winkel)/(Iterationen)/drehung; /// damit sollte er sich in der Letzten Iteration um Winkel drehen

	while (j<=Iterationen)
	{

		if (checkline_right(j*step,drehung,waittime)==1)
		{
			return 1;
		}
		if (checkline_left(j*step,drehung,waittime)==1)
		{
			return 1;
		}
		if (checkline_left(j*step,drehung,waittime)==1)
		{
			return 1;
		}
		if (checkline_right(j*step,drehung,waittime)==1)
		{
			return 1;
		}
		j++;

	}
	ecrobot_sound_tone(100, 2000, 10);
	return 0;
}

int check_Token()
{
	int TOUCH = 0;
	if (ecrobot_get_touch_sensor(NXT_PORT_S2)==1 || ecrobot_get_touch_sensor(NXT_PORT_S1)==1)
	{
		TOUCH = 1;
	}
	return TOUCH;
}

void drive_cm(float cm);

int forward(int Strecke) /// returns 1 if still on Black returns 0 if it left black and is on white

/// FORWARD GEHT DAVON AUS, DASS MAN SICH AUF SCHWARZ BEFINDET
/// IST MAN AUF WEIß, KANN ES SEIN DASS ER WEIß FÄLSCHLICHERWEISE ALS SCHWARZ ERKENNT UND WEITERFÄHRT

{
	int i;
	int waittime = 20;
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
			Light = forward(2);
		}
		Light = checkline(40,2);
	}
}
void Node_center_case1()
{
	int Light = 1;
	while(Light==1)
	{
		Light = forward(-2);
	}
	drive_cm(2);

}

void Node_center_case2()
{
	int i = 1;
	drive_cm(-9);
	int Light = 0;
	while (Light ==0 && i<4)
	{
		drive_cm(-2);
		Light = checkline(10*i,1);
		i++;
	}
	follow_line();
	drive_cm(7);
}

int goto_Node_center()
{
	int i;
	drive_cm(7);
	systick_wait_ms(1000);
	for (i=1;i<=2;i++)
	{
		if (checkline(10*i,i)==1)
		{
			Node_center_case1();
			ecrobot_sound_tone(500, 1000, 10);
			systick_wait_ms(1000);
			return 1;
		}
		systick_wait_ms(1000); ///evtl. wichtig sonst komische drehung
		drive_cm(2);
		systick_wait_ms(1000);
	}
	Node_center_case2();
	ecrobot_sound_tone(500, 1000, 10);
	systick_wait_ms(1000);
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
	ecrobot_sound_tone(500, 1000, 10);
	systick_wait_ms(1050);				/// Akustische Ausgabe


	display_clear(1);
	char str3[12] = "Kalibriert";
	display_goto_xy(5, 2);				/// Display Ausgabe
	display_string(str3);



	No_Line_Found = checkline(180,5); /// Zurück zur Linie

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
	int power = sgn(cm)* 80; //Prozentzahl für Motoren
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	while(abs(nxt_motor_get_count(NXT_PORT_B))< umdr && abs(nxt_motor_get_count(NXT_PORT_C))< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C , power , 0);
		nxt_motor_set_speed(NXT_PORT_B , power , 0);
		wait_ms(10);
		if(abs(nxt_motor_get_count(NXT_PORT_B)) > abs(nxt_motor_get_count(NXT_PORT_C)))//kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
		{
			nxt_motor_set_speed(NXT_PORT_B , power*(4/5), 0);
			while(abs(nxt_motor_get_count(NXT_PORT_B)) > abs(nxt_motor_get_count(NXT_PORT_C)))
			{
				nxt_motor_set_speed(NXT_PORT_C , power , 0);
				wait_ms(10);

			}
//			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
		}
		if(abs(nxt_motor_get_count(NXT_PORT_B)) < abs(nxt_motor_get_count(NXT_PORT_C)))
		{
			nxt_motor_set_speed(NXT_PORT_C , power*(4/5), 0);
			while( abs(nxt_motor_get_count(NXT_PORT_C)) > abs(nxt_motor_get_count(NXT_PORT_B)))
			{
				nxt_motor_set_speed(NXT_PORT_B , power , 0);
				wait_ms(10);
			}
//			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
		}
		if (check_Token() == 1)
		{
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
			Token_found();
		}
	}
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
}

/// Idee für ScanNode:
/// geradeaus = checkline(3);  --> Roboter sucht nach Linie und liefert sofort richtigen Wert
/// danach 2 Rotationen um 180°
/// bei der ersten muss er sicher wieder eine Linie finden, da er von da kommt --> Ausrichtung korrigieren mit checkline()
/// während einer Rotation nutzt die Funktion die schwell-variablen white und black aus
/// while (Rotation 180°)
///{
/// bei der ersten Rotation muss beachtet werden, ob er geradeaus was gefunden hat oder nicht,
/// denn dann startet er auf Weiß oder Schwarz
///
/// if (geradaus = 1) /// Start auf schwarz
/// 	Lichtaktuell = 1
///     while (Lichtaktuell = 1)
///
/// 		Miss das Licht
/// 		if (Licht < white) /// Licht SEHR weiß
/// 			Laufvariable++;
///				Lichtaktuell = 0 /// Licht ist jetzt weiß
///		while (Lichtaktuell = 0)
///			Miss das Licht
/// 		if (Licht > black) /// Licht SEHR schwarz
///
///}

int get_Hits(int MAX_grad,int Position)   /// GET_HITS SUCHT IMMER NACH RECHTS!!!

{

	int waittime = 20;
	int drehung = 5;

	int Light;
	int grad = 0;  // Zählvariable die die aktuelle Drehung mitverfolgt
	int Hits = 0;  // Zählvariable, die erhöht wird, wenn ein neuer schwarzer streifen entdeckt wird
	/// TODO drübergucken
	while(grad<MAX_grad)
	{
		while(Position==1 && grad < MAX_grad)
		{
			drehen_grad_r(drehung);			/// dreh dich ein stück
			systick_wait_ms(waittime);
			grad += 5;
			Light = ecrobot_get_light_sensor(NXT_PORT_S3); /// Miss Licht
			if (Light<white)
			{
				Position = 0; /// Er befindet sich jetzt auf Weißer oberfläche
			}
		}

		while(Position==0 && grad < MAX_grad)
		{
			drehen_grad_r(drehung);			/// dreh dich ein stück
			systick_wait_ms(waittime);
			grad += 5;
			Light = ecrobot_get_light_sensor(NXT_PORT_S3); /// Miss Licht
			if (Light>black)
			{
				Position = 1; /// Er befindet sich jetzt auf Schwarzer Oberfläche
				Hits++;

				ecrobot_sound_tone(300, 1000, 10);
			}

		}

	}
	return Hits;
}

void scan_Node()
{
	int left,right,straigth = 0;
	int drehung = 5;
	int waittime = 20;
	int i;



	straigth = goto_Node_center(); /// Roboter sucht vor sich nach einer Linie, findet er was richtet er sich aus und setzt variable 1

//		systick_wait_ms(1000);

	drehen_grad_r(20); 				/// Dreh 45°

//		systick_wait_ms(1000);

	right = get_Hits(90,0);			/// suche Linie rechts

//		systick_wait_ms(1000);

	if (checkline_right(24,drehung,waittime)==0)   /// Finde herkunftslinie
	{
		/// FATAL ERROR
		ecrobot_sound_tone(1000, 1000, 10);
		display_clear(1);
		char str4[14] = "LINIE VERLOREN";
		display_goto_xy(5, 2);				/// Display Ausgabe
		display_string(str4);
		while (1)
		{

		}
	}

//		systick_wait_ms(1000);

	drehen_grad_r(20);    /// Dreh 45°

//		systick_wait_ms(1000);

	left = get_Hits(90,0);   /// suche Linie links

//		systick_wait_ms(1000);

	drehen_grad_l(135);			/// drehe zurück richtung Herkunftslinie

	if (checkline_left(18,drehung,waittime)==0) /// Finde herkunftslinie
	{
		/// FATAL ERROR
		ecrobot_sound_tone(1000, 1000, 10);
		display_clear(1);
		char str4[14] = "LINIE VERLOREN";
		display_goto_xy(5, 2);				/// Display Ausgabe
		display_string(str4);
		while (1)
		{

		}
	}

//		systick_wait_ms(1000);

	drehen_grad_l(180);   /// drehe dich zurück zur Ausgangsstellung

//		ecrobot_sound_tone(1000,500,10);
//		systick_wait_ms(1050);


	///
	/// AUSGABE
	///

//		display_clear(1);
//		char str1[12] = "straigthxxx";
//		display_goto_xy(5, 2);				/// Display Ausgabe
//		display_string(str1);
//
//		systick_wait_ms(1000);
//
//		display_clear(1);
//		display_goto_xy(1,0);
//		display_int(straigth,5);
//
//		systick_wait_ms(1000);
//
//		display_clear(1);
//		char str2[12] = "leftxxxxxxx";
//		display_goto_xy(5, 2);				/// Display Ausgabe
//		display_string(str2);
//
//		systick_wait_ms(1000);
//
//		display_clear(1);
//		display_goto_xy(1,0);
//		display_int(left,5);
//
//		systick_wait_ms(1000);
//
//		display_clear(1);
//		char str3[12] = "rightxxxxxx";
//		display_goto_xy(5, 2);				/// Display Ausgabe
//		display_string(str3);
//
//		systick_wait_ms(1000);
//
//		display_clear(1);
//		display_goto_xy(1,0);
//		display_int(right,5);
//
//		systick_wait_ms(1000);
//		ecrobot_sound_tone(500, 1000, 10);
//		systick_wait_ms(1050);				/// Akustische Ausgabe

	///
	///
	///
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
//	int c = nxt_motor_get_count(NXT_PORT_C);
//	ecrobot_status_monitor("Hello, wuff");
//	display_clear(0);
//	char str3[12] = "Kalibriert";
//	display_goto_xy(5, 2);
//	display_string(str3);
//	display_goto_xy(1,3);
//	display_int(-b-c, 6);
//	wait_ms(500);
	dreh = -b; /// Korrektur von Thomas: hab aus b -b gemacht, weil dreh sonst negativ war.
}


int turn_left()
{
	drehen_grad_l(90);
	return checkline(40,2);
}

int turn_right()
{
	drehen_grad_r(90);
	return checkline(40,2);
}


#include "../h/Thomas.h"

////// Algo KRAM
//
//#define NORTH 0x10
//#define SOUTH 0x20
//#define WEST 0x40
//#define EAST 0x80
//
//
//
//// define maze size here
//#define MAZE_WIDTH 24
//#define MAZE_HEIGHT 24
//
//#define TOKEN_AIM 9999
//
//
////Absolute coordinates
//typedef struct coord{
//    int x;
//    int y;
//} coord;
//
//typedef struct node *maze;
//typedef struct node{
//    struct coord position;
//    maze compass[4];
//    int visited;
//    int bfs_reached_from;
//} node;
//struct node *current_node;
//
//
////einfach verkette Liste als Warteschlange im bfs
//typedef struct element *list;
//typedef struct element{
//    struct coord node_position;
//    struct element *next;
//} element;
//
//typedef struct instructions{
//    int path[50];
//} instructions;
//
//void list_append(struct element **start, struct coord discovered);
//
//void list_remove_first(struct element **start);
//
//void destroy_list(struct element *start);
//
//int list_search(struct element *start, struct coord tofind);
//
//void reset_nodes_bfs();
//
//void init();
//
//void discover();
//
//int direction_detect(int given_intersection, int wanted_direction);
//
//int turn_d(int direction);
//
//struct node *create_node();
//
//struct coord bfs_closest_unvisited_node();
//
//struct instructions bfs_path_to_node(struct coord goal);
//
//struct coord shift_coordinates(struct coord old, int direction);
//
//struct instructions create_path(struct coord goal_position);
//
//int follow_instructions(struct instructions instr);
//
//int main_loop();

////

#define NORTH 0x10
#define SOUTH 0x20
#define WEST 0x40
#define EAST 0x80

#define D_N     0x10    // North
#define D_S     0x20    // South
#define D_NS    0x30    // North and South
#define D_W     0x40    // West
#define D_NW    0x50    // North and West
#define D_SW    0x60    // South and West
#define D_NSW   0x70    // North, South and West
#define D_E     0x80    // East
#define D_NE    0x90    // North and East
#define D_SE    0xA0    // South and East
#define D_NSE   0xB0    // North, South and East
#define D_WE    0xC0    // West and East
#define D_NWE   0xD0    // North, West and East
#define D_SWE   0xE0    // South, West and East
#define D_NSWE  0xF0    // North, South, West and East
#define ROBOT_FAIL        0x00
#define ROBOT_SUCCESS     0x01
#define ROBOT_TOKENFOUND  0x02

int black;  /// MAXIMALES SCHWARZ minus Toleranz siehe: Get_Black_White
int white;  /// MININMALES WEIß plus Toleranz
float Toleranz_black = 0.7; /// Erfahrungswerte Anwendung siehe kalibrierung_farbe
float Toleranz_white = 0.2;
int dreh = 1030;  /// Gute Näherung, Kalibrierung in kalibrierung_drehen()

char Zeile1[15] = "Ich kalibriere";
char Zeile2[15]	= "die Helligkeit";
char Zeile3[15] = "   Farbwerte  ";
char Zeile4[15] = "       /      ";
char Zeile5[15] = " 360° Drehung ";
char Zeile6[15] = "dreh ist      ";


///-----------------------------------------------------------------------------------
/// HILFSFUNKTIONEN
///-----------------------------------------------------------------------------------

void wait_ms(int ms)  /// Diese Tolle Funktion lässt Zeit voranschreiten, ohne Motoren abzuschalten
{
	 int time =systick_get_ms();
	 while( systick_get_ms()> time + ms)
	 {
	 }
}

int sgn(float x) 	  /// einfache Signumfunktion
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

void printnumber(int zahl , int x, int y){
  display_goto_xy(x, y);
  display_int(zahl,3);
}

///-----------------------------------------------------------------------------------
///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///-----------------------------------------------------------------------------------







///-----------------------------------------------------------------------------------
/// TOKENFUNKIONEN
///-----------------------------------------------------------------------------------

int check_Token()
{
	int TOUCH = 0;
	if (ecrobot_get_touch_sensor(NXT_PORT_S2)==1 || ecrobot_get_touch_sensor(NXT_PORT_S1)==1)
	{
		TOUCH = 1;
	}
	return TOUCH;
}

void Token_found()   /// Wird aufgerufen, wenn Token gefunden #noshit


{
	/// TODO erhöhe Token Variable um 1
	ecrobot_sound_tone(500, 2000, 10);
	systick_wait_ms(10000);
}

///-----------------------------------------------------------------------------------
///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///-----------------------------------------------------------------------------------




///-----------------------------------------------------------------------------------
/// GRUNDLEGENDE FARHFUNKTIONEN
///-----------------------------------------------------------------------------------

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
	systick_wait_ms(20);
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
	systick_wait_ms(20);
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
	systick_wait_ms(20);
	// das hier ist wichtig, denn falls im letzten Schritt
	///der While Schleife beide nxt_motor_get_count den EXAKT selben Wert ausgeben wird keine der
	///beiden if bedingungen erfüllt und die Motoren werden nicht ausgeschaltet!!!
	///

}

///-----------------------------------------------------------------------------------
///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///-----------------------------------------------------------------------------------







///-----------------------------------------------------------------------------------
/// ERWEITERTE FAHRFUNKTIONEN
///-----------------------------------------------------------------------------------

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

///-----------------------------------------------------------------------------------
///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///-----------------------------------------------------------------------------------







///-----------------------------------------------------------------------------------
/// KALIBRIERFUNKIONEN
///-----------------------------------------------------------------------------------

void kalibrieren_farbe()
{
	display_clear(1);

	display_goto_xy(1, 1);				/// Display Ausgabe
	display_string(Zeile1);
	display_goto_xy(1, 2);
	display_string(Zeile2);



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

	display_goto_xy(1, 1);				/// Display Ausgabe
	display_string(Zeile3);
	display_goto_xy(1, 2);
	display_string(Zeile4);
	printnumber(black,5,2);
	printnumber(white,9,2);



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

void kalibrieren_drehen()
{
	/// Änderung von Thomas : hab das unten mal auskommentiert, da sonst die erzeugte black variable überschrieben wird
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int umdr = 900;
	int power = 80;


	display_goto_xy(1, 4);				/// Display Ausgabe
	display_string(Zeile1);
	display_goto_xy(1, 5);
	display_string(Zeile5);



//	while(-nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)
//	{
//		nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
//		nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
//		wait_ms(50);
//		if(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
//		{
//			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//			while(-nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
//			{
//				nxt_motor_set_speed(NXT_PORT_C , 80 , 0);
//				wait_ms(10);
//
//			}
//			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//		}
//		if(-nxt_motor_get_count(NXT_PORT_B) < nxt_motor_get_count(NXT_PORT_C))
//		{
//			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//			while(nxt_motor_get_count(NXT_PORT_C) > -nxt_motor_get_count(NXT_PORT_B))
//			{
//				nxt_motor_set_speed(NXT_PORT_B , -80 , 0);
//				wait_ms(10);
//
//			}
//			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
//		}
//	}
	while(abs(nxt_motor_get_count(NXT_PORT_B))< umdr && abs(nxt_motor_get_count(NXT_PORT_C))< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C , power , 0);
		nxt_motor_set_speed(NXT_PORT_B , -power , 0);
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
				nxt_motor_set_speed(NXT_PORT_B , -power , 0);
				wait_ms(10);
			}
//			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
		}
	}// bissel gedreht, jetzt Schwarz suchen
	while(ecrobot_get_light_sensor(NXT_PORT_S3)<=black)
	{
		nxt_motor_set_speed(NXT_PORT_C , power , 0);
		nxt_motor_set_speed(NXT_PORT_B , -power , 0);
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
				nxt_motor_set_speed(NXT_PORT_B , -power , 0);
				wait_ms(10);
			}
//			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
		}
	}// jetzt issa auf schwarz. Motoren aus
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
	//wait_ms(100);// evtl. nochma gucken, ob wa immanoch uff schwarz sind
	//jetzt drehungen vergleichen und dreh berechnen
	int b = nxt_motor_get_count(NXT_PORT_B);

	dreh = -b; /// Korrektur von Thomas: hab aus b -b gemacht, weil dreh sonst negativ war.


	display_clear(1);

	display_goto_xy(1, 1);				/// Display Ausgabe
	display_string(Zeile3);
	display_goto_xy(1, 2);
	display_string(Zeile4);
	printnumber(black,5,2);
	printnumber(white,9,2);

	display_goto_xy(1, 4);				/// Display Ausgabe
	display_string(Zeile6);
	printnumber(dreh,10,4);

}

void kalibrieren_Knoten();

///-----------------------------------------------------------------------------------
///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///-----------------------------------------------------------------------------------







///-----------------------------------------------------------------------------------
/// HILFSFUNKTIONEN ZUR KONTENERKUNDUNG
///-----------------------------------------------------------------------------------

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

int get_Hits(int MAX_grad,int Position)   /// GET_HITS SUCHT IMMER NACH RECHTS!!!

{
	int waittime = 20;
	int drehung = 5;

	int Light;
	int grad = 0;  // Zählvariable die die aktuelle Drehung mitverfolgt
	int Hits = 0;  // Zählvariable, die erhöht wird, wenn ein neuer schwarzer streifen entdeckt wird
	/// TODO drübergucken

	/// Korrektur falls Position falsch übergeben wurde

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

				ecrobot_sound_tone(300, 300, 50);
			}


		}

	}
	return Hits;
}
///-----------------------------------------------------------------------------------
///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///-----------------------------------------------------------------------------------







///-----------------------------------------------------------------------------------
/// FAHRFUNKTIONEN FÜR SCHNITTSTELLE
///-----------------------------------------------------------------------------------

void go_straight()
{
	follow_line(10,1);
}

int scan()
{


	int left,right,straigth;
	int drehung = 5;
	int waittime = 20;
	int i;


	for (i=0;i<3;i++)
	{
		drive_cm(2);
		systick_wait_ms(200);
	}

	straigth = checkline(20,2);
	if (straigth == 1) {ecrobot_sound_tone(300, 300, 50);}
	 /// Roboter sucht vor sich nach einer Linie, findet er was richtet er sich aus und setzt variable 1

//		systick_wait_ms(1000);

	drehen_grad_r(20); 				/// Dreh 45°

//		systick_wait_ms(1000);

	right = get_Hits(90,0);			/// suche Linie rechts
	if (right == 0){}
	else {right = 1;}

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
	if (left == 0){}
	else {left = 1;}

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
	int orientation = 0;
	int intersection = 0;
	switch(orientation)
	{
			case 0: if (straigth) intersection |= D_N;
					if (right) intersection |= D_E;
					intersection |= D_S;
					if (left) intersection |= D_W;
					break;
			case 1: if (left) intersection |= D_N;
					if (straigth) intersection |= D_E;
					if (right) intersection |= D_S;
					intersection |= D_W;
					break;
			case 2: intersection |= D_N;
					if (left) intersection |= D_E;
					if (straigth) intersection |= D_S;
					if (right) intersection |= D_W;
					break;
			case 3: if (right) intersection |= D_N;
					intersection |= D_E;
					if (left) intersection |= D_S;
					if (straigth) intersection |= D_W;
					break;
			default: return 0;
	}

	display_clear(1);
	printnumber(left,1,1);
	printnumber(straigth,3,2);
	printnumber(right,5,1);
	return intersection;
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

///-----------------------------------------------------------------------------------
///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///-----------------------------------------------------------------------------------

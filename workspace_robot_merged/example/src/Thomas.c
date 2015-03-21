//#include "../h/Thomas.h"
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

// define maze size here
#define MAZE_WIDTH 24
#define MAZE_HEIGHT 24

#define TOKEN_AIM 9999


//Absolute coordinates
typedef struct coord{
    int x;
    int y;
} coord;

typedef struct node *maze;
typedef struct node{
    struct coord position;
    maze compass[4];
    int visited;
    int bfs_reached_from;
} node;
struct node *current_node;


//einfach verkette Liste als Warteschlange im bfs
typedef struct element *list;
typedef struct element{
    struct coord node_position;
    struct element *next;
} element;

typedef struct instructions{
    int path[50];
} instructions;

void list_append(struct element **start, struct coord discovered);

void list_remove_first(struct element **start);

void destroy_list(struct element *start);

int list_search(struct element *start, struct coord tofind);

void reset_nodes_bfs();

void init();

void discover();

int direction_detect(int given_intersection, int wanted_direction);

int turn_d(int direction);

struct node *create_node();

struct coord bfs_closest_unvisited_node();

struct instructions bfs_path_to_node(struct coord goal);

struct coord shift_coordinates(struct coord old, int direction);

struct instructions create_path(struct coord goal_position);

int follow_instructions(struct instructions instr);

void wait_ms(int ms);   /// Hilfsfunktionen
int sgn(float x);

void kalibrieren_drehen();  /// Kalibrierungsfunktionen
void kalibrieren_farbe();

void drehen_grad_r(int grad);
void drehen_grad_l(int grad);			/// Grundlegende Bewegungsfunktionen
void drive_cm(float cm);


int turn_left();                       /// Funktionen, die vom algo benötigt werden.
int turn_right();

void Token_found();						/// Token Funkionen
int check_Token();


void go_straight();
void kalibrieren_Knoten();
void drive_cm2(float cm);
void printnumber(int zahl , int x, int y);


void follow_line();

int checkline_right (int steps, int drehung, int waittime);
int checkline_left (int steps, int drehung, int waittime);

int checkline(int Winkel,int Iterationen);

int forward();						/// erweiterte Bewegungsfunktionen
int goto_Node_center();
void Node_center_case1();
void Node_center_case2();

int get_Hits(int MAX_grad,int Position);
int scan();

int main_loop();
int black;  /// MAXIMALES SCHWARZ minus Toleranz siehe: Get_Black_White
int white;  /// MININMALES WEIß plus Toleranz
float Toleranz_black = 0.7; /// Erfahrungswerte Anwendung siehe kalibrierung_farbe
float Toleranz_white = 0.2;
int dreh = 1030;  /// Gute Näherung, Kalibrierung in kalibrierung_drehen()



//Current orientation of bot
int orientation;

//map of pointers to node objects
struct node *ptrmap[2 * MAZE_WIDTH + 3][2 * MAZE_HEIGHT + 3];
struct node *current_node;

int tokencount;
int discovered_everything;

struct coord current_position;


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



void drive_cm2(float cm)
{
	float umdr =sgn(cm) *cm * 2000/97;
	int power = sgn(cm)* 80; //Prozentzahl für Motoren

	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);

	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);

	while(abs(nxt_motor_get_count(NXT_PORT_B))< umdr && abs(nxt_motor_get_count(NXT_PORT_C))< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C , power , 0);
		nxt_motor_set_speed(NXT_PORT_B , power , 0);
	}
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
}

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
	char KalibriereFarbe[20] = "Ich Kalibriere Farbe";
	display_goto_xy(12, 4);				/// Display Ausgabe
	display_string(KalibriereFarbe);

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
	char ErgebnisKalibrierung[23] = "Farbwerte black / white";
	display_goto_xy(5, 2);				/// Display Ausgabe
	display_string(ErgebnisKalibrierung);



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
	if (ecrobot_get_light_sensor(NXT_PORT_S3)<white)
	{
		Position = 0;
	}
	if (ecrobot_get_light_sensor(NXT_PORT_S3)>black)
	{
		Position = 1;
	}

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
			while( grad < MAX_grad)
			{
				drehen_grad_r(drehung);			/// dreh dich ein stück
				systick_wait_ms(waittime);
				grad += 5;
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


	int left,right,straigth = 0;
	int drehung = 5;
	int waittime = 20;
	int i;


	for (i=0;i<3;i++)
	{
		drive_cm(2);
		systick_wait_ms(200);
	}
	display_clear(1);
	printnumber(1,3,3);
	straigth = checkline(20,2);
	 /// Roboter sucht vor sich nach einer Linie, findet er was richtet er sich aus und setzt variable 1

//		systick_wait_ms(1000);
	printnumber(2,4,3);
	drehen_grad_r(20); 				/// Dreh 45°

//		systick_wait_ms(1000);
	printnumber(3,5,3);
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
void init(){
	int i, j;
	for(i = 0; i < 2 * MAZE_HEIGHT + 2; i++){
		for(j = 0; j < 2* MAZE_WIDTH + 2; j++) {
			ptrmap[i][j] = NULL;
		}
	}
	current_node = create_node();
	ptrmap[current_position.x + MAZE_WIDTH][current_position.y + MAZE_HEIGHT] =
			current_node;
	tokencount = 0;
	discovered_everything = 0;
}


//Discover surrounding connected nodes and create them in map
void discover(){

	if (!current_node->visited){
		int new_intersection = 0;
		new_intersection = scan();
		//go through all possible directions, look if there are undiscovered
		// nodes nearby
		int i;
		for (i = 0; i <= 3; i++) {
			struct coord neighbour_position =
					shift_coordinates(current_position,i);
			if (direction_detect(new_intersection, i)) {
				if (ptrmap[neighbour_position.x + MAZE_WIDTH]
				[neighbour_position.y + MAZE_WIDTH]
						== NULL) {
					struct node *discovered_node = create_node();
					//update ptrmap with new node
					ptrmap[neighbour_position.x + MAZE_WIDTH]
					[neighbour_position.y + MAZE_HEIGHT] =
							discovered_node;
					discovered_node->position = neighbour_position;
				}
				//set up pointers of current and new node, fill in new nodes position
				current_node->compass[i] = ptrmap[neighbour_position.x + MAZE_WIDTH]
				[neighbour_position.y +
								MAZE_HEIGHT];
				ptrmap[neighbour_position.x + MAZE_WIDTH]
				[neighbour_position.y + MAZE_HEIGHT]
						->compass[(i+2) % 4] = current_node;
			}

		}
		current_node->visited = 1; //current node is explored
	}
}


//Returns 1 if the wanted cardinal direction is available at a intersection,
//0 if not
int direction_detect(int given_intersection, int wanted_direction) {
	//Northern node?
	if ( ((given_intersection >> 4)&1) && (wanted_direction == NORTH ||
			wanted_direction == 0)) {
		return 1;
	}

		//Eastern node?
	else if (((given_intersection >> 7)&1) && (wanted_direction == EAST ||
			wanted_direction == 1)) {
		return 1;
	}

		//Southern node?
	else if (((given_intersection >> 5)&1) && (wanted_direction == SOUTH ||
			wanted_direction == 2)) {
		return 1;
	}

		//Western node?
	else if (((given_intersection >> 6)&1) &&
			(wanted_direction == WEST || wanted_direction == 3)){
		return 1;
	}
	return 0;
}

//turn bot in a specific direction
int turn_d(int direction){
	while (orientation != direction){
		turn_left();
	}
	orientation = direction;
	return ROBOT_SUCCESS;
}

//return pointer to new, empty node
struct node *create_node(){
	struct node *new_node;
	new_node = malloc(sizeof(struct node));
	new_node->visited = 0;
	int i;
	for (i=0; i<4; i++){
		new_node->compass[i]=NULL;
	}
	new_node->position.x = 0;
	new_node->position.y = 0;
	return new_node;
}

//look for graph-wise closest unvisited node and return its coord
struct coord bfs_closest_unvisited_node() {
	int i;
	struct element  *queue;
	queue = NULL;
	struct element *seen;
	seen = NULL;
	struct coord wanted;
	struct coord position;
	list_append(&queue,current_position);
	struct coord neighbour_position;
	do {
		position = queue->node_position;
		list_append(&seen, position);
		for (i = 3; i >= 0; i--) {
			neighbour_position = shift_coordinates(position,i);
			if ((ptrmap[position.x + MAZE_WIDTH][position.y +
					MAZE_HEIGHT])->compass[i] != NULL) {
				if (ptrmap[position.x + MAZE_WIDTH][position.y + MAZE_HEIGHT]
						->compass[i]->visited == 0) {
					wanted = shift_coordinates(position, i);
					destroy_list(queue);
					destroy_list(seen);
					return wanted; //return the coords of found node
				}

				if (!list_search(seen,neighbour_position) &&
						!list_search(queue,neighbour_position)){
					list_append(&queue, neighbour_position);
				}
			}
		}
		list_remove_first(&queue);
	} while (queue != NULL);
	discovered_everything = 1;
	return current_position;
}

//look for shortest path to given coordinates
struct instructions bfs_path_to_node(struct coord goal) {
	int i;
	struct element  *queue;
	queue = NULL;
	struct element *seen;
	seen = NULL;
	struct instructions path_to_goal;
	struct coord cur_position;
	cur_position = current_position;
	current_node->bfs_reached_from = 8;
	list_append(&queue,cur_position);

	struct coord neighbour_position;

	while (queue != NULL) {
		list_append(&seen, cur_position);
		if ((cur_position.x  == goal.x) && (cur_position.y == goal.y)){
			path_to_goal = create_path(goal);
			reset_nodes_bfs();
			destroy_list(queue);
			destroy_list(seen);
			return path_to_goal;
		}

		for (i = 3; i >= 0; i--) {
			neighbour_position = shift_coordinates(cur_position,i);
			if ((ptrmap[cur_position.x + MAZE_WIDTH]
			[cur_position.y + MAZE_HEIGHT])->compass[i] != NULL) {
				if ((!list_search(seen,neighbour_position)) &&
						(!list_search(queue,neighbour_position))){
					list_append(&queue, neighbour_position);
					ptrmap[neighbour_position.x + MAZE_WIDTH]
					[neighbour_position.y + MAZE_HEIGHT]
							->bfs_reached_from = i;
				}
			}
		}

		list_remove_first(&queue);
		cur_position = queue->node_position;
	}

	path_to_goal.path[0] = 8;
	return path_to_goal;
}

//appends the list the given pointer is pointing to with the given coord
void list_append(struct element **start, struct coord discovered) {

	struct element **previous = start;
	struct element *current = *start;
	while (current != NULL) {
		previous = &(current->next);
		current = current->next;
	}
	struct element *new_element = malloc(sizeof(struct element));
	new_element->node_position = discovered;
	new_element->next = NULL;
	*previous = new_element;
}

//remove the first entry of a list and update the pointer the dp is pointing to
void list_remove_first(struct element **start) {

	struct element *temp;

	if (*start == NULL) {
		return;
	}
	temp = *start;
	*start = temp->next;
	free(temp);
}


//completely free the list given at start
void destroy_list (struct element *start) {
	while (start != NULL) {
		struct element *next = start->next;
		free(start);
		start = next;
	}
}

int list_search(struct element *start, struct coord tofind) {
	struct element *iter = start;
	while (iter != NULL){
		if (iter->node_position.x == tofind.x &&
				iter->node_position.y == tofind.y) {
			return 1;
		}
		iter = iter->next;
	}
	return 0;
}

void reset_nodes_bfs(){
	int i, j;
	for(i = 0; i < 2 * MAZE_HEIGHT + 3; i++){
		for(j = 0; j < 2 * MAZE_WIDTH + 3; j++) {
			if (ptrmap[i][j] != NULL) {
				ptrmap[i][j]->bfs_reached_from = 9;
			}
		}
	}
}

//translates iterable and pre-defined directions and returns the respective
// coords
struct coord shift_coordinates(struct coord old, int direction){
	switch (direction) {
		case 0:
			old.y += 1;
			return old;
		case NORTH:
			old.y += 1;
			return old;
		case 1:
			old.x += 1;
			return old;
		case EAST:
			old.x += 1;
			return old;
		case 2:
			old.y -= 1;
			return old;
		case SOUTH:
			old.y -= 1;
			return old;
		case 3:
			old.x -= 1;
			return old;
		case WEST:
			old.x -= 1;
			return old;
		default: return old;
	}
}

int follow_instructions(struct instructions instr){
	int i;
	for (i = 0; instr.path[i] != 8; i++){
		turn_d(instr.path[i]);
		go_straight();
	}
	return ROBOT_SUCCESS;
}

struct instructions create_path(struct coord goal_position){
	struct instructions temp;
	struct instructions path_to_goal;
	int i;
	for (i=0; (goal_position.x != current_position.x)
			|| (goal_position.y != current_position.y); i++){
		temp.path[i] = ptrmap[goal_position.x + MAZE_WIDTH]
		[goal_position.y + MAZE_HEIGHT]->bfs_reached_from;
		if (temp.path[i] == 9) {
		}
		goal_position = shift_coordinates(goal_position, (temp.path[i] + 2) % 4);
	}
	int j;
	for (j = 0, i -= 1; i >= 0; i--, j++){
		path_to_goal.path[j] = temp.path[i];
	}
	path_to_goal.path[j] = 8;
	return path_to_goal;
}


int main_loop(){
	current_position.x = 0;
	current_position.y = 0;
	orientation = 2;

	//main loop
	int i = 0;
	while (!(tokencount >= TOKEN_AIM || discovered_everything)){
		discover();
		return EXIT_SUCCESS;
		follow_instructions(bfs_path_to_node
				(bfs_closest_unvisited_node()));
		i++;
	}
	if (discovered_everything) {
		return EXIT_SUCCESS;
	}
	struct coord optimum;
	optimum.x = 0;
	optimum.y = 0;
	follow_instructions(bfs_path_to_node(optimum));
	return EXIT_SUCCESS;
}









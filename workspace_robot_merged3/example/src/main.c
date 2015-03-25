#include "../h/main.h"

/// DO NOT DELETE THIS METHOD
/// It is called every 1ms and e.g. can be used for implementing a
/// real time counter / clock.
void user_1ms_isr_type2(void) {
}

void ecrobot_device_initialize(void) {
}

void ecrobot_device_terminate(void) {
}
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
#define MAZE_WIDTH 7
#define MAZE_HEIGHT 7

#define TOKEN_AIM 1

//Current orientation of bot
char orientation;

//map of pointers to node objects
struct node *ptrmap[2 * MAZE_WIDTH][MAZE_HEIGHT + 2];
struct node *current_node;
struct coord current_position;

char tokencount;
char discovered_everything;

struct instructions *global_instructions;

int black;  /// MAXIMALES SCHWARZ minus Toleranz siehe: Get_Black_White
int white;  /// MININMALES WEI� plus Toleranz
float Toleranz_black = 0.7; /// Erfahrungswerte Anwendung siehe kalibrierung_farbe
float Toleranz_white = 0.2;
int dreh = 1030;  /// Gute N�herung, Kalibrierung in kalibrierung_drehen()

char Zeile1[15] = "Ich kalibriere";
char Zeile2[15]	= "die Helligkeit";
char Zeile3[15] = "   Farbwerte  ";
char Zeile4[15] = "       /      ";
char Zeile5[15] = " 360 Drehung ";
char Zeile6[15] = "dreh ist      ";

char StringLinks[15] = "LINKS         ";
char StringGeradeaus[15] = "GERADEAUS     ";
char StringRechts[15] = "RECHTS        ";


///-----------------------------------------------------------------------------------
/// HILFSFUNKTIONEN
///-----------------------------------------------------------------------------------

void wait_ms(int ms)  /// Diese Tolle Funktion l�sst Zeit voranschreiten, ohne Motoren abzuschalten
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
/// TOKENFUNKIONEN
///----------------
///-----------------------------------------------------------------------------------
///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///-----------------------------------------------------------------------------------




///-----------------------------------------------------------------------------------
/// GRUNDLEGENDE FARHFUNKTIONEN
///-----------------------------------------------------------------------------------

void drive_cm(float cm)
{

	float umdr =sgn(cm) * cm * 2000/97;
	int power = sgn(cm)* 85; //Prozentzahl f�r Motoren
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

		//check for token
		if (ecrobot_get_touch_sensor(NXT_PORT_S2) || ecrobot_get_touch_sensor(NXT_PORT_S1))
		{
			nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
			nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
			tokencount += 1;
			ecrobot_sound_tone(220, 1000, 35);
			systick_wait_ms(10000);		}
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
	while(abs(nxt_motor_get_count(NXT_PORT_B))< umdr && abs(nxt_motor_get_count(NXT_PORT_C))< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C , -power , 0);
		nxt_motor_set_speed(NXT_PORT_B , power , 0);
		wait_ms(10);
//		if(abs(nxt_motor_get_count(NXT_PORT_B)) > abs(nxt_motor_get_count(NXT_PORT_C)))//kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
//		{
//			nxt_motor_set_speed(NXT_PORT_B , power*(4/5), 0);
//			while(abs(nxt_motor_get_count(NXT_PORT_B)) > abs(nxt_motor_get_count(NXT_PORT_C)))
//			{
//				nxt_motor_set_speed(NXT_PORT_C , -power , 0);
//				wait_ms(10);
//			}
//			nxt_motor_set_speed(NXT_PORT_B , power, 0);
//		}
//		else
//		{
//			if(abs(nxt_motor_get_count(NXT_PORT_B)) < abs(nxt_motor_get_count(NXT_PORT_C)))
//			{
//				nxt_motor_set_speed(NXT_PORT_C , -power*(4/5), 0);
//				while( abs(nxt_motor_get_count(NXT_PORT_C)) > abs(nxt_motor_get_count(NXT_PORT_B)))
//				{
//					nxt_motor_set_speed(NXT_PORT_B , power , 0);
//					wait_ms(10);
//				}
//				nxt_motor_set_speed(NXT_PORT_C , -power, 0);
//			}
//		}
	}
	/// Korrektur von Thomas
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	systick_wait_ms(5);
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
	while(abs(nxt_motor_get_count(NXT_PORT_B))< umdr && abs(nxt_motor_get_count(NXT_PORT_C))< umdr)//bis einer die Umdrehungen erreicht hat
	{
		nxt_motor_set_speed(NXT_PORT_C , power , 0);
		nxt_motor_set_speed(NXT_PORT_B , -power , 0);
		wait_ms(10);
//		if(abs(nxt_motor_get_count(NXT_PORT_B)) > abs(nxt_motor_get_count(NXT_PORT_C)))//kucken, ob einer mehr umdrehungen hat	                                                                 // und dann entsprehend angleichen
//		{
//			nxt_motor_set_speed(NXT_PORT_B , -power*(4/5), 0);
//			while(abs(nxt_motor_get_count(NXT_PORT_B)) > abs(nxt_motor_get_count(NXT_PORT_C)))
//			{
//				nxt_motor_set_speed(NXT_PORT_C , power , 0);
//				wait_ms(10);
//			}
//			nxt_motor_set_speed(NXT_PORT_B , -power, 0);
//		}
//		else
//		{
//		if(abs(nxt_motor_get_count(NXT_PORT_B)) < abs(nxt_motor_get_count(NXT_PORT_C)))
//			{
//				nxt_motor_set_speed(NXT_PORT_C , power*(4/5), 0);
//				while( abs(nxt_motor_get_count(NXT_PORT_C)) > abs(nxt_motor_get_count(NXT_PORT_B)))
//				{
//					nxt_motor_set_speed(NXT_PORT_B , -power , 0);
//					wait_ms(10);
//				}
//				nxt_motor_set_speed(NXT_PORT_C , power, 0);
//			}
//		}

	}
	/// Korrektur von Thomas
	nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
	nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
	systick_wait_ms(5);
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
	int waittime = 5;
	int drehung = 5;

	int step = (Winkel)/(Iterationen)/drehung; /// damit sollte er sich in der Letzten Iteration um Winkel drehen

	while (j<=Iterationen)
	{

		if (checkline_right(j*step,drehung,waittime))
		{
			return 1;
		}
		if (checkline_left(j*step,drehung,waittime))
		{
			return 1;
		}
		wait_ms(15);
		if (checkline_left(j*step,drehung,waittime))
		{
			return 1;
		}
		if (checkline_right(j*step,drehung,waittime))
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
/// IST MAN AUF WEI�, KANN ES SEIN DASS ER WEI� F�LSCHLICHERWEISE ALS SCHWARZ ERKENNT UND WEITERF�HRT

{
	int i;
	int waittime = 20;
	for (i=0;i<10;i++)
	{
		if (ecrobot_get_light_sensor(NXT_PORT_S3)<white) /// ist es sehr wei� hier?
		{
			return 0;
		}
		drive_cm(Strecke);
		systick_wait_ms(waittime);

	}
	return 1;

}

void go_straight(){ /// follow_line f�hrt bis zum n�chsten Knoten

	/// FOLLOW-LINE GEHT DAVON AUS, DASS MAN AUF SCHWARZ IST

	while (checkline(32,2)){
		while (forward(1)){}
	}

	systick_wait_ms(100);
	int i;
	for (i=0;i<2;i++){
		drive_cm(4.3);
		systick_wait_ms(20);
	}

	switch (orientation){
	        case 0: current_position.y += 1;
	            break;
	        case 1: current_position.x += 1;
	            break;
	        case 2: current_position.y -= 1;
	            break;
	        case 3: current_position.x -= 1;
	            break;
	}
	current_node = ptrmap[current_position.x + MAZE_WIDTH]
						 [current_position.y + MAZE_HEIGHT];
}

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
			MAX_BLACK = Light; /// Aktualisiere h�chsten Black wert
		}
		if (Light<MIN_WHITE)
		{
			MIN_WHITE = Light; /// Aktualisiere niedrigsten White wert
		}

		drehen_grad_r(5); /// Dreh dich! ~360�
		wait_ms(20);


	}

	white = MIN_WHITE + (MAX_BLACK - MIN_WHITE)*Toleranz_white;  /// DEFINIERE GLOBALE VARIABLEN UM
	black = MAX_BLACK - (MAX_BLACK - MIN_WHITE)*Toleranz_black;

	ecrobot_sound_tone(500, 1000, 10);
	systick_wait_ms(1050);				/// Akustische Ausgabe


	display_clear(1);

	display_goto_xy(1, 1);				/// Display Ausgabe
	display_string(Zeile3);
	display_goto_xy(1, 2);
	display_string(Zeile4);
	printnumber(black,5,2);
	printnumber(white,9,2);



	No_Line_Found = checkline(180,5); /// Zur�ck zur Linie

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
	/// �nderung von Thomas : hab das unten mal auskommentiert, da sonst die erzeugte black variable �berschrieben wird
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	int umdr = 900;


	display_goto_xy(1, 4);				/// Display Ausgabe
	display_string(Zeile1);
	display_goto_xy(1, 5);
	display_string(Zeile5);



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


	dreh = - nxt_motor_get_count(NXT_PORT_B);


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


///-----------------------------------------------------------------------------------
///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///-----------------------------------------------------------------------------------
/*
int get_Hits(int MAX_grad,int Position)   /// GET_HITS SUCHT IMMER NACH RECHTS!!!

{
	int waittime = 20;
	int drehung = 5;

	int Light;
	int grad = 0;  // Z�hlvariable die die aktuelle Drehung mitverfolgt
	int Hits = 0;  // Z�hlvariable, die erh�ht wird, wenn ein neuer schwarzer streifen entdeckt wird
	/// TODO dr�bergucken

	/// Korrektur falls Position falsch �bergeben wurde

	while(grad<MAX_grad)
	{
		while(Position==1 && grad < MAX_grad)
		{
			drehen_grad_r(drehung);			/// dreh dich ein st�ck
			systick_wait_ms(waittime);
			grad += 5;
			Light = ecrobot_get_light_sensor(NXT_PORT_S3); /// Miss Licht
			if (Light<white)
			{
				Position = 0; /// Er befindet sich jetzt auf Wei�er oberfl�che
			}
		}

		while(Position==0 && grad < MAX_grad)
		{
			drehen_grad_r(drehung);			/// dreh dich ein st�ck
			systick_wait_ms(waittime);
			grad += 5;
			Light = ecrobot_get_light_sensor(NXT_PORT_S3); /// Miss Licht
			if (Light>black)
			{
				Position = 1; /// Er befindet sich jetzt auf Schwarzer Oberfl�che
				Hits++;

				ecrobot_sound_tone(300, 300, 50);
			}


		}

	}
	return Hits;
}
*/
///-----------------------------------------------------------------------------------
/// FAHRFUNKTIONEN F�R SCHNITTSTELLE
///-----------------------------------------------------------------------------------

int scan()
{


	int left,right,straigth;

	straigth = checkline(30,1);
	if (straigth) {ecrobot_sound_tone(300, 300, 50);}
	/// Roboter sucht vor sich nach einer Linie, findet er was richtet er sich aus und setzt variable 1

//		systick_wait_ms(1000);

	drehen_grad_r(90); 				/// Dreh 45�

	right = checkline(30,1);
	if (right) {ecrobot_sound_tone(300, 300, 50);}

	drehen_grad_r(180);

	left = checkline(30,1);
	if (left) {ecrobot_sound_tone(300, 300, 50);}


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
	if (left){
		display_goto_xy(1,1);
		display_string(StringLinks);
	}
	if (right){
		display_goto_xy(1,2);
		display_string(StringRechts);
	}
	if (straigth){
		display_goto_xy(1,3);
		display_string(StringGeradeaus);
	}
	drehen_grad_r(90);
	return intersection;
}


///-----------------------------------------------------------------------------------
///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///-----------------------------------------------------------------------------------


void init(){
	tokencount = 0;
	discovered_everything = 0;
	orientation = 2;
	int i, j;
	for(i = 0; i < 2 * MAZE_WIDTH; i++){
		for(j = 0; j < MAZE_HEIGHT + 2; j++) {
			ptrmap[i][j] = NULL;
		}
	}
	current_node = create_node();
	ptrmap[current_position.x + MAZE_WIDTH][current_position.y + MAZE_HEIGHT] =
			current_node;
	current_node->visited = 1;
	ptrmap[current_position.x + MAZE_WIDTH][current_position.y - 1 + MAZE_HEIGHT] =
				create_node();

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
	else if (((given_intersection >> 6)&1) && (wanted_direction == WEST ||
			wanted_direction == 3)){
		return 1;
	}
	return 0;
}

//turn bot in a specific direction
void turn_d(int direction){
	int diff = ((orientation - direction + 4)%4);
	switch (diff){
		case 0:
			break;
		case 1:
			drehen_grad_l(90);
			break;
		case 2:
			drehen_grad_r(180);
			break;
		case 3:
			drehen_grad_r(90);

			break;
	}
	checkline(40,2);
	orientation = direction;
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
struct instructions *bfs_path_to_node(struct coord goal) {
	int i;
	struct element  *queue;
	queue = NULL;
	struct element *seen;
	seen = NULL;
	struct coord cur_position;
	cur_position = current_position;
	current_node->bfs_reached_from = 8;
	list_append(&queue,cur_position);

	struct coord neighbour_position;

	while (queue != NULL) {
		list_append(&seen, cur_position);
		if ((cur_position.x  == goal.x) && (cur_position.y == goal.y)){
			global_instructions = create_path(goal);
			reset_nodes_bfs();
			destroy_list(queue);
			destroy_list(seen);
			return global_instructions;
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

	global_instructions->path[0] = 8;
	return global_instructions;
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
	struct element *iter;
	while (start != NULL) {
		iter = start->next;
		free(start);
		start = iter;
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
	for(i = 0; i < 2 * MAZE_WIDTH; i++){
		for(j = 0; j < MAZE_HEIGHT + 2; j++) {
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
		case 1:
			old.x += 1;
			return old;
		case 2:
			old.y -= 1;
			return old;
		case 3:
			old.x -= 1;
			return old;
		default: return old;
	}
}

int follow_instructions(struct instructions *instr){
	int i;
	for (i = 0; instr->path[i] != 8; i++){
		turn_d(instr->path[i]);
		go_straight();
		instr->path[i] = 9;
	}
	i++;
	instr->path[i] = 9;
	return ROBOT_SUCCESS;
}

struct instructions *create_path(struct coord goal_position){
	struct instructions temp;
	int i;
	for (i=0; (goal_position.x != current_position.x)
			|| (goal_position.y != current_position.y); i++){
		temp.path[i] = ptrmap[goal_position.x + MAZE_WIDTH]
		[goal_position.y + MAZE_HEIGHT]->bfs_reached_from;
		goal_position = shift_coordinates(goal_position, (temp.path[i] + 2) % 4);
	}
	int j;
	for (j = 0, i -= 1; i >= 0; i--, j++){
		global_instructions->path[j] = temp.path[i];
	}
	global_instructions->path[j] = 8;
	return global_instructions;
}

TASK(OSEK_Main_Task) {
		ecrobot_set_light_sensor_active(NXT_PORT_S3);
		kalibrieren_farbe();
		kalibrieren_drehen();
		current_position.x = 0;
		current_position.y = 1;
		init();
		go_straight();
		//main loop
		while (!(tokencount >= TOKEN_AIM || discovered_everything)){
			discover();
			follow_instructions(bfs_path_to_node(bfs_closest_unvisited_node()));
		}

		if (discovered_everything && (tokencount != TOKEN_AIM)) {
			ecrobot_sound_tone(220,1000,35);
			while(1){}
			return;
		}

		struct coord optimum;
		optimum.x = 0;
		optimum.y = 1;
		follow_instructions(bfs_path_to_node(optimum));
		ecrobot_sound_tone(220,1000,35);
		while(1){}
		return;
}

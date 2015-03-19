/*
// * david.c
// *
// *  Created on: 17.03.2015
// *      Author: David
// */
//#include "../h/david.h"
//#include "../h/Thomas.h"
///*
// * Zeit überbrücken, um z.B. Motoren laufen zu lassen
// */
//void wait_ms(int ms){
//	 int time =systick_get_ms();
//	 while( systick_get_ms()> time + ms)
//	 {
//	 }
//}
//
//void drehen_grad_r(int grad){
//
//	float umdr = (grad * 8/3) - 5;// 1°drehen entspricht 2.66° Raddrehen, 10 grad weniger wg. Traegheit
//	int power = 75; //Prozentzahl für Motoren
//	nxt_motor_set_count(NXT_PORT_B, 0);
//	nxt_motor_set_count(NXT_PORT_C, 0);
//	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
//	{
//		nxt_motor_set_speed(NXT_PORT_C , power , 0);
//		nxt_motor_set_speed(NXT_PORT_B , -power , 0);
//		wait_ms(60);
//		nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//		nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
////		if(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat
////			                                                                 // und dann entsprehend angleichen
////		{
////			while(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
////			{
////				nxt_motor_set_speed(NXT_PORT_C , power , 0);
////				wait_ms(20);
////				nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
////			}
////		}
////		else
////		{
////			while(nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
////			{
////				nxt_motor_set_speed(NXT_PORT_B , power , 0);
////				wait_ms(100);
////				nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
////			}
////		}
//	}
//}
//
//void drehen_grad_l(int grad)
//{
//
//	float umdr = (grad * 8/3) - 5;// 1°drehen entspricht 2.66° Raddrehen, 10 grad weniger wg. Trägheit
//	int power = 75; //Prozentzahl für Motoren
//	nxt_motor_set_count(NXT_PORT_B, 0);
//	nxt_motor_set_count(NXT_PORT_C, 0);
//	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
//	{
//		nxt_motor_set_speed(NXT_PORT_C , -power , 0);
//		nxt_motor_set_speed(NXT_PORT_B , power , 0);
//		wait_ms(60);
//		nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//		nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
////		if(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat
////			                                                                 // und dann entsprehend angleichen
////		{
////			while(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
////			{
////				nxt_motor_set_speed(NXT_PORT_C , power , 0);
////				wait_ms(20);
////				nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
////			}
////		}
////		else
////		{
////			while(nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
////			{
////				nxt_motor_set_speed(NXT_PORT_B , power , 0);
////				wait_ms(100);
////				nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
////			}
////		}
//	}
//}
//void drehen()
//{
//	int umdr = 950;// 360 grad drehen bei ca.950 grad Raddrehen
//	int power = 75; //Prozentzahl für Motoren
//	nxt_motor_set_count(NXT_PORT_B, 0);
//	nxt_motor_set_count(NXT_PORT_C, 0);
//	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
//	{
//		nxt_motor_set_speed(NXT_PORT_C , power , 0);
//		nxt_motor_set_speed(NXT_PORT_B , -power , 0);
//		wait_ms(50);
//		nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//		nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
////		if(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))//kucken, ob einer mehr umdrehungen hat
////			                                                                 // und dann entsprehend angleichen
////		{
////			while(nxt_motor_get_count(NXT_PORT_B) > nxt_motor_get_count(NXT_PORT_C))
////			{
////				nxt_motor_set_speed(NXT_PORT_C , power , 0);
////				wait_ms(20);
////				nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
////			}
////		}
////		else
////		{
////			while(nxt_motor_get_count(NXT_PORT_C) > nxt_motor_get_count(NXT_PORT_B))
////			{
////				nxt_motor_set_speed(NXT_PORT_B , power , 0);
////				wait_ms(100);
////				nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
////			}
////		}
//	}
//	wait_ms(6000);
//}
///*erst: mitttig auf Knoten, dann:
// *
// * orientieren:???
// * dreht sich und gibt dann die knotenzahl für den Knoten aus.
// */
//void scanNode(int orientation)
//{
//
//}
//
//
///* bisschen vorwärts fahren: DAS MIT DEM WARTEN MUSS ÜBERARBEITET WERDN!
//* Zu Tun:
//* Drehen, bis Umdrehungszahl erreicht ist.
//*
//* Fehlerbehandlung:
//* - wenn der nach soundso lange nicht dreht, prozentzahl höherstellen.
//* - Motoren sollen gleiche Umdrrehungen gemacht haben
//*/
//
//
//void drive(int umdr)
//{
//	int power = 60; //Prozentzahl für Motoren
//	nxt_motor_set_count(NXT_PORT_B, 0);
//	nxt_motor_set_count(NXT_PORT_C, 0);
//	while(nxt_motor_get_count(NXT_PORT_B)< umdr && nxt_motor_get_count(NXT_PORT_C)< umdr)//bis einer die Umdrehungen erreicht hat
//	{
//		nxt_motor_set_speed(NXT_PORT_C , power , 0);
//		nxt_motor_set_speed(NXT_PORT_B , power , 0);
//		wait_ms(100);
//		nxt_motor_set_speed(NXT_PORT_C , 0 , 1);
//		nxt_motor_set_speed(NXT_PORT_B , 0 , 1);
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
//	}
//
//}



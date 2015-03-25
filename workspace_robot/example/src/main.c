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

/* void hello_world() {
	ecrobot_status_monitor("Hello, World");
}
*/



TASK(OSEK_Main_Task)
{

	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	nxt_motor_set_speed(NXT_PORT_A , 60 , 0);
	kalibrieren_farbe();
	systick_wait_ms(1000);
	kalibrieren_drehen();

	while (1)
	{
		follow_line();
		int a = scan();
		turn_left();
	}
//	int a = main_loop();
//	discover();




}


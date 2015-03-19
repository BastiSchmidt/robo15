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
	while (1)
	{
		ecrobot_set_light_sensor_active(NXT_PORT_S3);
		ecrobot_status_monitor("Hello, World");
//		display_clear(0);
//		char str3[12] = "GRADEAUS";
//		display_goto_xy(5,2);
//		display_string(str3);
		kalibrieren_drehen();
		/* 2000msec wait */
		systick_wait_ms(2000);
	}

}


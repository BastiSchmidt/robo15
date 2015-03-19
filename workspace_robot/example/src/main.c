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
	int SCHWARZ = ecrobot_get_light_sensor(NXT_PORT_S3)-300;
	Get_Black_White();
	while (1)
	{
		ecrobot_set_light_sensor_active(NXT_PORT_S3);
		ecrobot_status_monitor("Hello, thomas13 ");

		checkline(black);
		drive_cm(5);
		systick_wait_ms(1000);


	}

}


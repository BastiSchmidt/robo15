#include "../h/Configuration.h"

int main(void) {

	//get current date to create new version number
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	printf("Version %02d%02d%02d\n", timeinfo->tm_mday, timeinfo->tm_hour,
			timeinfo->tm_min);

/*	//example code...
 	printf("Token: %d\n", Robot_Move(0, 0));
	printf("Intersection: %d\n", Robot_GetIntersections());
	printf("Token: %d\n", Robot_Move(1, 0));
	printf("Intersection: %d\n", Robot_GetIntersections());
	printf("Token: %d\n", Robot_Move(2, 0));
	Robot_Move(3,-5);
	printf("Intersection: %0x\n", Robot_GetIntersections());*/
	current_position.x = 0;
	current_position.y = 0;
	orientation = SOUTH;

	init_sim_rnd();

	init();

	//randomly searching for all nodes - highly wasteful
	int i = 0, r, d;
	while (i < 00){
		discover();
		//print_matrix(0);
		print_ptrmap();
		printf("%d\n", i);
		printf("Current orientation: %0x\n", orientation);

		do {
			d = 8;
			srand(time(NULL) + rand()); //more random is more random
			for (r = rand() % 4; r >= 0; r--){
				d = d * 2; //yields directions (16,32,64,128) - really!
			}
		} while (!direction_detect(scan(), d));

		turn_d(d);
		go_straight();
		i++;
	}

	return EXIT_SUCCESS;
}

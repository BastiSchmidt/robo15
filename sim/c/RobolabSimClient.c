#include "../h/Configuration.h"

int main(void) {
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
	x_pos = 0;
	y_pos = 0;

	init_sim_rnd();

	//randomly searching for all nodes - highly wasteful
	int i = 0;
	while (i < 100000){
		discover();
		print_matrix();
		srand(time(NULL) + rand()); //more random is more random
		int r, d = 8;
		for (r = rand() % 4; r >= 0; r--){
			d = d * 2; //yields directions (16,32,64,128) - really!
		}
		if (direction_detect(Robot_GetIntersections(),d)){
			move_d(d);
		}
		i++;
	}

	return EXIT_SUCCESS;
}

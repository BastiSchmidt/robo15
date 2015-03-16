#include "../h/Configuration.h"

int main(void) {
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
	printf("Intersection: %0x\n", Robot_GetIntersections());
	printf("%0x\n", move_d(SOUTH));
	return EXIT_SUCCESS;
}

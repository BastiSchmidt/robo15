#include "../h/Configuration.h"

int main(void) {
/*	printf("Token: %d\n", Robot_Move(0, 0));
	printf("Intersection: %d\n", Robot_GetIntersections());
	printf("Token: %d\n", Robot_Move(1, 0));
	printf("Intersection: %d\n", Robot_GetIntersections());
	printf("Token: %d\n", Robot_Move(2, 0));*/
	Robot_Move(3,-5);
	printf("Intersection: %0x\n", Robot_GetIntersections());
	return EXIT_SUCCESS;
}

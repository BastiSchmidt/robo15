#include "../h/Configuration.h"

int main(void) {

	//get current date to create new version number
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	printf("Version %02d%02d%02d\n", timeinfo->tm_mday, timeinfo->tm_hour,
			timeinfo->tm_min);

	current_position.x = 0;
	current_position.y = 0;
	Robot_Move(current_position.x, current_position.y);
	orientation = 2;

	//init_sim_rnd();

	init();

	//randomly searching for all nodes - highly wasteful
	int i = 0, r, d;
	struct coord optimum;
	while (!(tokencount >= TOKEN_AIM || discovered_everything)){
		discover();
		print_ptrmap();
		optimum = bfs_closest_unvisited_node();
		printf("X:%d Y: %d I:%d\n",optimum.x, optimum.y, i);
		follow_instructions(bfs_path_to_node(optimum));
		/*do {
			d = 8;
			srand(time(NULL) + rand()); //more random is more random
			for (r = rand() % 4; r >= 0; r--){
				d = d * 2; //yields directions (16,32,64,128) - really!
			}
		} while (!direction_detect(scan(), d));

		turn_d(d);
		go_straight();*/
		i++;
	}
	if (discovered_everything) {
		printf("Discovered all nodes...");
		return EXIT_SUCCESS;
	}
	optimum.x = 0;
	optimum.y = 0;
	follow_instructions(bfs_path_to_node(optimum));
	printf("Found all tokens: %d tokens.\n", tokencount);
	return EXIT_SUCCESS;
}

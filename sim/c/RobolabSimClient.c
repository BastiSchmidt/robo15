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

	//main loop
	int i = 0;
	struct coord optimum;
	while (!(tokencount >= TOKEN_AIM || discovered_everything)){
		discover();
		optimum = bfs_closest_unvisited_node();
		follow_instructions(bfs_path_to_node(optimum));
		i++;
	}
	if (discovered_everything && (tokencount != TOKEN_AIM)) {
		printf("Discovered all nodes...");
		return EXIT_SUCCESS;
	}
	optimum.x = 0;
	optimum.y = 0;
	follow_instructions(bfs_path_to_node(optimum));
	printf("Found all tokens: %d tokens.\n", tokencount);
	return EXIT_SUCCESS;
}

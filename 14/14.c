#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACT_FLYING  0
#define ACT_RESTING 1

struct reindeer {
	unsigned int speed;
	unsigned int fly; // Time spent flying
	unsigned int rest; // Time spent resting
	unsigned int pos;
	unsigned int timer;
	unsigned int action;
	unsigned int points;
} reindeer[9];

int main(void) {
	FILE *input = fopen("input", "r");
	if (input == NULL) {
		printf("Could not open input file\n");
		exit(EXIT_FAILURE);
	}
	char buf[16]; // Dummy buffer, we don't really care about reindeer names
	unsigned int cur = 0;
	bzero((void*)reindeer, sizeof(reindeer));
	while (1) {
		unsigned int speed, fly, rest;
		int tmp = fscanf(input, "%s can fly %u km/s for %u seconds, but then must rest for %u seconds.", buf, &speed, &fly, &rest);
		if (tmp < 0) break;
		reindeer[cur].speed = speed;
		reindeer[cur].fly = fly;
		reindeer[cur].rest = rest;
		reindeer[cur].timer = fly;
		cur++;
	}
	unsigned int i, j;
	for (i=0; i < 2503; i++) { // Simulate 2503 seconds of racing
		for (j=0; j < 9; j++) {
			if (reindeer[j].action == ACT_FLYING) reindeer[j].pos += reindeer[j].speed;
			reindeer[j].timer--;
			if (reindeer[j].timer == 0) {
				reindeer[j].action = !reindeer[j].action;
				if (reindeer[j].action == ACT_FLYING) reindeer[j].timer = reindeer[j].fly;
				else reindeer[j].timer = reindeer[j].rest;
			}
		}
		// Find the lead distance; any reindeer tied for the lead get a point
		int lead = 0;
		for (j=0; j < 9; j++) if (reindeer[j].pos > lead) lead = reindeer[j].pos;
		for (j=0; j < 9; j++) if (reindeer[j].pos == lead) reindeer[j].points++;
	}
	int max_pos = 0;
	int max_pts = 0;
	for (i=0; i < 9; i++) {
		if (reindeer[i].pos > max_pos) max_pos = reindeer[i].pos;
		if (reindeer[i].points > max_pts) max_pts = reindeer[i].points;
	}
	printf("Part One Solution: %d\n", max_pos);
	printf("Part Two Solution: %d\n", max_pts);
	fclose(input);
	return EXIT_SUCCESS;
}

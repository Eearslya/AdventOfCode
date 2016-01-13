#include <stdio.h>
#include <stdlib.h>

struct ingredient {
	int cap; // capacity
	int dur; // durability
	int fla; // flavor
	int tex; // texture
	int cal; // calories
} ings[16];

int main(void) {
	FILE *input = fopen("input", "r");
	if (input == NULL) {
		printf("Could not open input file\n");
		exit(EXIT_FAILURE);
	}
	char buf[32]; // Dummy buffer to dump ingredient names
	unsigned int i;
	unsigned int done = 0;
	unsigned int confirm;
	unsigned int cur = 0;
	while (1) {
		int cap, dur, fla, tex, cal;
		int tmp = fscanf(input, "%s capacity %d, durability %d, flavor %d, texture %d, calories %d", buf, &cap, &dur, &fla, &tex, &cal);
		if (tmp < 0) break;
		ings[cur].cap = cap;
		ings[cur].dur = dur;
		ings[cur].fla = fla;
		ings[cur].tex = tex;
		ings[cur].cal = cal;
		cur++;
	}
	unsigned int max = 0;
	unsigned int max_lowcal = 0; // Max score at 500 calories
	unsigned char *amts;
	amts = malloc(sizeof(unsigned char) * cur);
	for (i=0; i < cur; i++) amts[i] = 0;
	while (1) {
		// Iterate through EVERY combination of 0-100 for every ingredient
		for (i=(cur-1); i >= 0; i--) {
			amts[i]++;
			if (amts[i] < 101) break;
			if (i == 0) {
				done = 1;
				break;
			}
			amts[i] = 0;
		}
		if (done) break;
		// Make sure the combination we came up with adds up to 100
		confirm = 0;
		for (i=0; i < cur; i++) confirm += amts[i];
		if (confirm != 100) continue;
		// Calculate score/calories
		int cap = 0, dur = 0, fla = 0, tex = 0, cal = 0;
		for (i=0; i < cur; i++) {
			cap += amts[i] * ings[i].cap;
			dur += amts[i] * ings[i].dur;
			fla += amts[i] * ings[i].fla;
			tex += amts[i] * ings[i].tex;
			cal += amts[i] * ings[i].cal;
		}
		// Individual scores cannot be lower than 0
		if (cap < 0) cap = 0;
		if (dur < 0) dur = 0;
		if (fla < 0) fla = 0;
		if (tex < 0) tex = 0;
		unsigned int score = cap*dur*fla*tex;
		if (score > max) max = score;
		if (cal == 500 && score > max_lowcal) max_lowcal = score;
	}
	printf("Part One Solution: %u\n", max);
	printf("Part Two Solution: %u\n", max_lowcal);
	fclose(input);
	return EXIT_SUCCESS;
}

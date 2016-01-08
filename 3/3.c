#include <stdio.h>
#include <stdlib.h>

int deliver(FILE*,int);

int main(void) {
	FILE *input = fopen("input", "r");
	if (input == NULL) {
		printf("Could not open input file.\n");
		exit(EXIT_FAILURE);
	}
	printf("Part One Solution: %d\n", deliver(input, 0));
	printf("Part Two Solution: %d\n", deliver(input, 1));
	fclose(input);
	return EXIT_SUCCESS;
}

int deliver(FILE *input, int robosanta) {
	unsigned char houses[512][512]; // Technically, this is wrong, since the puzzle says the houses are infinite. But it works for our purposes.
	int x = 256;
	int y = 256;
	int x2 = x;
	int y2 = y;
	int which_santa = 0;
	int total_houses = 0;
	int i, j, xdelta, ydelta;
	for (i=0; i < 512; i++) {
		for (j=0; j < 512; j++) {
			houses[i][j] = 0;
		}
	}
	houses[x][y] = 1; // He automatically delivers to his starting location
	rewind(input);
	while (1) {
		char cmd = fgetc(input);
		xdelta = 0;
		ydelta = 0;
		if (cmd == '^') ydelta++;
		else if (cmd == 'v') ydelta--;
		else if (cmd == '<') xdelta--;
		else if (cmd == '>') xdelta++;
		else break; // End of file
		if (which_santa == 0) {
			x += xdelta;
			y += ydelta;
			houses[x][y]++;
			if (robosanta == 1) which_santa = 1; // Only swap santas if we're doing part two
		}
		else {
			x2 += xdelta;
			y2 += ydelta;
			houses[x2][y2]++;
			which_santa = 0;
		}
	}
	for (i=0; i < 512; i++) {
		for (j=0; j < 512; j++) {
			if (houses[i][j] > 0) total_houses++;
		}
	}
	return total_houses;
}

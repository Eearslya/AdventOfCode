#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH  100
#define HEIGHT 100
#define STEPS  100

int run_lights(FILE*,unsigned int);

unsigned char grid_cur[WIDTH][HEIGHT];
unsigned char grid_new[WIDTH][HEIGHT];

int main(void) {
	FILE *input = fopen("input", "r");
	if (input == NULL) {
		printf("Could not open input file\n");
		exit(EXIT_FAILURE);
	}
	printf("Part One Solution: %d\n", run_lights(input, 1));
	printf("Part Two Solution: %d\n", run_lights(input, 2));
	fclose(input);
	return EXIT_SUCCESS;
}

int run_lights(FILE *input, unsigned int part) {
	rewind(input);
	unsigned int i, j, step;
	int x, y;
	for (i=0; i < HEIGHT; i++) {
		for (j=0; j < WIDTH; j++) {
			if (fgetc(input) == '#') grid_cur[j][i] = 1;
			else grid_cur[j][i] = 0;
		}
		fgetc(input);
	}
	for (step=0; step < STEPS; step++) {
		if (part == 2) {
			grid_cur[0][0] = 1;
			grid_cur[0][HEIGHT-1] = 1;
			grid_cur[WIDTH-1][0] = 1;
			grid_cur[WIDTH-1][HEIGHT-1] = 1;
		}
		for (i=0; i < HEIGHT; i++) {
			for (j=0; j < WIDTH; j++) {
				unsigned int neighbors_on = 0;
				int tmpx, tmpy;
				for (x=-1; x < 2; x++) {
					tmpx = j + x;
					if (tmpx < 0 || tmpx >= WIDTH) continue;
					for (y=-1; y < 2; y++) {
						if (x == 0 && y == 0) continue;
						tmpy = i + y;
						if (tmpy < 0 || tmpy >= HEIGHT) continue;
						neighbors_on += grid_cur[tmpx][tmpy];
					}
				}
				grid_new[j][i] = grid_cur[j][i];
				if (grid_cur[j][i] == 1) {
					if (neighbors_on != 2 && neighbors_on != 3) grid_new[j][i] = 0;
				}
				else {
					if (neighbors_on == 3) grid_new[j][i] = 1;
				}
			}
		}
		memcpy((void*)grid_cur, (void*)grid_new, sizeof(grid_new));
		if (part == 2) {
			grid_cur[0][0] = 1;
			grid_cur[0][HEIGHT-1] = 1;
			grid_cur[WIDTH-1][0] = 1;
			grid_cur[WIDTH-1][HEIGHT-1] = 1;
		}
	}
	unsigned int on = 0;
	for (i=0; i < HEIGHT; i++) {
		for (j=0; j < WIDTH; j++) {
			on += grid_cur[j][i];
		}
	}
	return on;
}

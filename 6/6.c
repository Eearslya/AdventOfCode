#include <stdio.h>
#include <stdlib.h>

#define CMD_ON  1
#define CMD_OFF 2
#define CMD_TOG 3

int main(void) {
	FILE *input = fopen("input", "r");
	unsigned char gridone[1000][1000];
	unsigned char gridtwo[1000][1000];
	unsigned int i, j, x, y, x2, y2, action, countone, counttwo;
	char command[8];
	if (input == NULL) {
		printf("Could not open input file\n");
		exit(EXIT_FAILURE);
	}
	// Init both grids
	for (i=0; i < 1000; i++) {
		for (j=0; j < 1000; j++) {
			gridone[i][j] = 0;
			gridtwo[i][j] = 0;
		}
	}
	while (1) {
		int read = fscanf(input, "%s", command); // Fetch initial command; either 'turn' or 'toggle'
		if (read < 0) break; // End of file, no more commands
		// Then get the rest of the params based on that
		if (command[1] == 'u') { // 'turn'
			fscanf(input, "%s %d,%d through %d,%d", command, &x, &y, &x2, &y2);
			if (command[1] == 'n') action = CMD_ON;
			else action = CMD_OFF;
		}
		else { // 'toggle'
			fscanf(input, "%d,%d through %d,%d", &x, &y, &x2, &y2);
			action = CMD_TOG;
		}
		for (i=x; i <= x2; i++) {
			for (j=y; j <= y2; j++) {
				if (action == CMD_TOG) {
					gridone[i][j] = !gridone[i][j];
					gridtwo[i][j] += 2;
				}
				else if (action == CMD_ON) {
					gridone[i][j] = 1;
					gridtwo[i][j] += 1;
				}
				else {
					gridone[i][j] = 0;
					if (gridtwo[i][j] > 0) gridtwo[i][j] -= 1;
				}
			}
		}
	}
	countone = 0;
	counttwo = 0;
	for (i=0; i < 1000; i++) {
		for (j=0; j < 1000; j++) {
			countone += gridone[i][j];
			counttwo += gridtwo[i][j];
		}
	}
	printf("Part One Solution: %d\n", countone);
	printf("Part Two Solution: %d\n", counttwo);
	fclose(input);
	return EXIT_SUCCESS;
}

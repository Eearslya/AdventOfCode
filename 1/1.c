#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *input = fopen("input", "r");
	if (input == NULL) {
		printf("No input file found.\n");
		exit(EXIT_FAILURE);
	}
	int floor = 0;
	int pos_at_basement = -1;
	int pos = 0;
	while (1) {
		char ins = fgetc(input);
		pos++;
		if (ins == '(') floor++;
		else if (ins == ')') floor--;
		else break;
		if (floor == -1 && pos_at_basement == -1) pos_at_basement = pos;
	}
	printf("Part One Solution: %d\n", floor);
	printf("Part Two Solution: %d\n", pos_at_basement);
	fclose(input);
	return EXIT_SUCCESS;
}

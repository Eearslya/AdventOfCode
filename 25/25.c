#include <stdio.h>
#include <stdlib.h>

#define COLUMN 3029 // Puzzle input
#define ROW    2947 // Puzzle input

int main(void) {
	unsigned int col, row, return_row;
	col = 1;
	row = 2;
	return_row = row; // The row we snap back to when we've finished our diagonal traversal
	unsigned long code = 20151125;
	while (1) {
		code = (code * 252533) % 33554393;
		if (col == COLUMN && row == ROW) break;
		col++;
		row--;
		if (row == 0) {
			row = ++return_row;
			col = 1;
		}
	}
	printf("Part One Solution: %lu\n", code);
	printf("Part Two Solution: Finish the other puzzles!\n");
	return EXIT_SUCCESS;
}

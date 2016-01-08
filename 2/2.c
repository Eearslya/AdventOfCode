#include <stdio.h>
#include <stdlib.h>

int min(int,int,int);

int main(void) {
	FILE *input = fopen("input", "r");
	if (input == NULL) {
		printf("Could not open input file.\n");
		exit(EXIT_FAILURE);
	}
	int l, w, h, lw, wh, lh, paper, ribbon;
	paper = 0;
	ribbon = 0;
	while (1) {
		int count = fscanf(input, "%dx%dx%d", &l, &w, &h);
		if (count < 0) break; // Reached the end of the file.
		paper += (2*l*w) + (2*w*h) + (2*l*h); // Surface area of present
		lw = l*w; // Find the smallest side's area for extra paper
		wh = w*h;
		lh = l*h;
		paper += min(lw, wh, lh);
		lw = l+l+w+w; // Find the smallest side's perimeter for ribbon length
		wh = w+w+h+h;
		lh = l+l+h+h;
		ribbon += min(lw, wh, lh);
		ribbon += (l*w*h); // Plus the present's volume
	}
	printf("Part One Solution: %d\n", paper);
	printf("Part Two Solution: %d\n", ribbon);
	fclose(input);
	return EXIT_SUCCESS;
}

int min(int a, int b, int c) {
	int r = a;
	if (r > b) r = b;
	if (r > c) r = c;
	return r;
}

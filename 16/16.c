#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// What we know about our target 'sue'
#define AKITAS      0
#define CATS        7
#define CARS        2
#define CHILDREN    3
#define GOLDFISH    5
#define PERFUMES    1
#define POMERANIANS 3
#define SAMOYEDS    2
#define TREES       3
#define VIZSLAS     0

int getsue(FILE*,unsigned int);

int main(void) {
	FILE *input = fopen("input", "r");
	if (input == NULL) {
		printf("Could not open input file\n");
		exit(EXIT_FAILURE);
	}
	printf("Part One Solution: %d\n", getsue(input, 1));
	printf("Part Two Solution: %d\n", getsue(input, 2));
	fclose(input);
	return EXIT_SUCCESS;
}

int getsue(FILE *input, unsigned int part) {
	rewind(input);
	unsigned int i, j, a, b, c, z;
	char sa[16], sb[16], sc[16];
	for (i=0; i < 500; i++) {
		int tmp = fscanf(input, "Sue %d: %s %d, %s %d, %s %d\n", &z, sa, &a, sb, &b, sc, &c);
		if (tmp < 0) {
			printf("Error reading file: Not enough sues!\n");
			exit(EXIT_FAILURE);
		}
		int akitas = -1, cats = -1, cars = -1, children = -1, goldfish = -1,
			perfumes = -1, pomeranians = -1, samoyeds = -1, trees = -1,
			vizslas = -1;
		for (j=0; j < 3; j++) {
			char *attr;
			int amt;
			if (j == 0) {
				attr = sa;
				amt = a;
			}
			else if (j == 1) {
				attr = sb;
				amt = b;
			}
			else {
				attr = sc;
				amt = c;
			}
			switch(attr[0]) {
			case 'a': akitas = amt; break;
			case 'c':
				switch(attr[2]) {
				case 'i': children = amt; break;
				case 'r': cars = amt; break;
				case 't': cats = amt; break;
				}
				break;
			case 'g': goldfish = amt; break;
			case 'p':
				if (attr[1] == 'e') perfumes = amt;
				else pomeranians = amt;
				break;
			case 's': samoyeds = amt; break;
			case 't': trees = amt; break;
			case 'v': vizslas = amt; break;
			}
		}
		if (akitas != -1 && akitas != AKITAS) continue;
		if (cars != -1 && cars != CARS) continue;
		if (children != -1 && children != CHILDREN) continue;
		if (perfumes != -1 && perfumes != PERFUMES) continue;
		if (samoyeds != -1 && samoyeds != SAMOYEDS) continue;
		if (vizslas != -1 && vizslas != VIZSLAS) continue;
		if (part == 1) {
			if (cats != -1 && cats != CATS) continue;
			if (goldfish != -1 && goldfish != GOLDFISH) continue;
			if (pomeranians != -1 && pomeranians != POMERANIANS) continue;
			if (trees != -1 && trees != TREES) continue;
		}
		else {
			if (cats != -1 && cats <= CATS) continue;
			if (goldfish != -1 && goldfish >= GOLDFISH) continue;
			if (pomeranians != -1 && pomeranians >= POMERANIANS) continue;
			if (trees != -1 && trees <= TREES) continue;
		}
		break;
	}
	return i+1;
}	

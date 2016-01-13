#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CITIES 16
#define NUM_PATHS  16

int get_city(char*);
unsigned int get_dist(unsigned int,unsigned int);
unsigned int init_city(unsigned int,char*);
void add_path(unsigned int,unsigned int,unsigned int);

struct path {
	unsigned int to;
	unsigned int distance;
};

struct city {
	char *name;
	struct path paths[NUM_PATHS];
	unsigned int path_count;
} cities[NUM_CITIES];

int main(void) {
	FILE *input = fopen("input", "r");
	char from[32], to[32];
	unsigned int distance, city_count, i, j, min_distance, max_distance;
	min_distance = -1; // Set to maximum unsigned int for later comparisons
	max_distance = 0;
	city_count = 0;
	// Initialize our struct arrays
	for (i=0; i < NUM_CITIES; i++) {
		cities[i].name = NULL;
		cities[i].path_count = 0;
		for (j=0; j < NUM_PATHS; j++) {
			cities[i].paths[j].to = 0;
			cities[i].paths[j].distance = 0;
		}
	}
	// Populate our arrays
	while (1) {
		int tmp = fscanf(input, "%s to %s = %d", from, to, &distance);
		if (tmp < 0) break; // End of file
		int fid = get_city(from);
		int tid = get_city(to);
		if (fid == -1) fid = init_city(city_count++, from);
		if (tid == -1) tid = init_city(city_count++, to);
		add_path(fid, tid, distance);
		add_path(tid, fid, distance);
	}
	unsigned char *path, *confirm;
	unsigned int done = 0;
	path = calloc(sizeof(unsigned char) * city_count, 1);
	confirm = calloc(sizeof(unsigned char) * city_count, 1);
	while (1) {
		// Clumsy but effective, simply brute-force all possible sequences.
		for (i=(city_count-1); i >= 0; i--) {
			path[i]++;
			if (path[i] < city_count) break; // If there's no carry-over, we can stop here.
			if (i == 0) { // If we're trying to increment the first value above max, it means we're done.
				done = 1;
				break;
			}
			path[i] = 0; // Carry the value over to the next iteration, reset this one
		}
		if (done) break; // We've gone to the max value and beyond, we're done
		// We need to make sure this path goes through all the cities
		unsigned int valid = 1;
		for (i=0; i < city_count; i++) confirm[i] = 0; // Reset the array
		for (i=0; i < city_count; i++) confirm[path[i]]++; // Account for every city passed through
		for (i=0; i < city_count; i++) {
			if (confirm[i] == 0) {
				valid = 0; // If any city was missed, this sequence is invalid
				break; // Don't bother checking any more
			}
		}
		if (!valid) continue; // Skip invalid paths
		unsigned int dist = 0;
		for (i=0; i < (city_count-1); i++) { // Traverse the path and add up all the distances
			dist += get_dist(path[i], path[i+1]);
		}
		if (dist < min_distance) min_distance = dist;
		if (dist > max_distance) max_distance = dist;
	}
	printf("Part One Solution: %d\n", min_distance);
	printf("Part Two Solution: %d\n", max_distance);
	// Cleanup
	free(path);
	free(confirm);
	for (i=0; i < NUM_CITIES; i++) if (cities[i].name != NULL) free(cities[i].name);
	fclose(input);
	return EXIT_SUCCESS;
}

int get_city(char *name) {
	int i;
	for (i=0; i < NUM_CITIES; i++) {
		if (cities[i].name == NULL) return -1;
		if (strcmp(cities[i].name, name) == 0) return i;
	}
	return -1;
}

unsigned int get_dist(unsigned int from, unsigned int to) {
	int i;
	for (i=0; i < cities[from].path_count; i++) {
		if (cities[from].paths[i].to == to) return cities[from].paths[i].distance;
	}
	return 0;
}

unsigned int init_city(unsigned int id, char *name) {
	cities[id].name = malloc(strlen(name)+1);
	strcpy(cities[id].name, name);
	return id;
}

void add_path(unsigned int from, unsigned int to, unsigned int distance) {
	unsigned int path = cities[from].path_count;
	cities[from].paths[path].to = to;
	cities[from].paths[path].distance = distance;
	cities[from].path_count++;
}
	

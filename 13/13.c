#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_solution(unsigned int);
int get_person(char*);
unsigned int init_person(char*);
void add_relation(unsigned int,unsigned int,int);
int get_relation(unsigned int,unsigned int);

struct relation {
	unsigned int person;
	int change;
};

struct person {
	char *name;
	struct relation relations[16];
	unsigned int num_relations;
} people[16];

int main(void) {
	FILE *input = fopen("input", "r");
	if (input == NULL) {
		printf("Could not open input file\n");
		exit(EXIT_FAILURE);
	}
	bzero((void*)people, sizeof(people));
	char person[16], action[5], neighbor[16];
	int change;
	unsigned int i;
	while (1) {
		int tmp = fscanf(input, "%s would %s %d happiness units by sitting next to %s", person, action, &change, neighbor);
		if (tmp < 0) break;
		neighbor[strlen(neighbor)-1] = 0; // Strip the trailing period
		int pid = get_person(person);
		int nid = get_person(neighbor);
		if (pid == -1) pid = init_person(person);
		if (nid == -1) nid = init_person(neighbor);
		if (action[0] == 'l') change = 0 - change;
		add_relation(pid, nid, change);
	}
	printf("Part One Solution: %d\n", get_solution(1));
	printf("Part Two Solution: %d\n", get_solution(2));
	for (i=0; i < 16; i++) if (people[i].name != NULL) free(people[i].name);
	fclose(input);
	return EXIT_SUCCESS;
}

int get_solution(unsigned int part) {
	unsigned int count = 0;
	unsigned int i;
	int max_change = 0;
	for (i=0; i < 16; i++) if (people[i].name != NULL) count++;
	if (part == 2) count++; // Part two adds "me" to the table.
	unsigned char *layout, *confirm;
	unsigned int done = 0;
	layout = calloc(sizeof(unsigned char) * count, 1);
	confirm = calloc(sizeof(unsigned char) * count, 1);
	while (1) {
		for (i=(count-1); i >= 0; i--) {
			layout[i]++;
			if (layout[i] < count) break;
			if (i == 0) {
				done = 1;
				break;
			}
			layout[i] = 0;
		}
		if (done) break;
		unsigned int valid = 1;
		for (i=0; i < count; i++) confirm[i] = 0;
		for (i=0; i < count; i++) confirm[layout[i]]++;
		for (i=0; i < count; i++) if (confirm[i] == 0) valid = 0;
		if (!valid) continue;
		int total_change = 0;
		for (i=0; i < count; i++) {
			int pid = layout[i];
			int nid;
			if (i == (count-1)) nid = layout[0];
			else nid = layout[i+1];
			total_change += get_relation(pid, nid);
			total_change += get_relation(nid, pid);
		}
		if (total_change > max_change) max_change = total_change;
	}
	free(layout);
	free(confirm);
	return max_change;
}

int get_person(char *name) {
	unsigned int i;
	for (i=0; i < 16; i++) {
		if (people[i].name == NULL) return -1;
		if (strcmp(people[i].name, name) == 0) return i;
	}
	return -1;
}

unsigned int init_person(char *name) {
	unsigned int i;
	for (i=0; i < 16; i++) {
		if (people[i].name != NULL) continue;
		people[i].name = malloc(strlen(name)+1);
		strcpy(people[i].name, name);
		break;
	}
	return i;
}

void add_relation(unsigned int p, unsigned int n, int c) {
	unsigned int i = people[p].num_relations;
	people[p].relations[i].person = n;
	people[p].relations[i].change = c;
	people[p].num_relations++;
}

int get_relation(unsigned int p, unsigned int n) {
	unsigned int i;
	for (i=0; i < people[p].num_relations; i++) {
		if (people[p].relations[i].person == n) return people[p].relations[i].change;
	}
	return 0;
}

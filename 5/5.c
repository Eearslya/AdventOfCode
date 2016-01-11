#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 16

int niceone(char*);
int nicetwo(char*);

int main(void) {
	FILE *input = fopen("input", "r"); // Puzzle input
	char string[STRING_LEN]; // 16-character strings
	unsigned int nicestr_one = 0;
	unsigned int nicestr_two = 0;
	if (input == NULL) {
		printf("Could not open input file!\n");
		exit(EXIT_FAILURE);
	}
	while (1) {
		if (fread((void*)string, sizeof(string), 1, input) > 1) break; // We reached EOF mid-read (shouldn't happen unless file is malformed)
		nicestr_one += niceone(string);
		nicestr_two += nicetwo(string);
		if (fgetc(input) == EOF) break; // We reached EOF at the end of the line
	}
	printf("Part One Solution: %d\n", nicestr_one);
	printf("Part Two Solution: %d\n", nicestr_two);
	fclose(input);
	return EXIT_SUCCESS;
}

int niceone(char *str) {
	unsigned int i, tmp;
	// At least 3 vowels
	tmp = 0;
	for (i=0; i < STRING_LEN; i++) {
		if (str[i] == 'a' ||
		    str[i] == 'e' ||
		    str[i] == 'i' ||
		    str[i] == 'o' ||
		    str[i] == 'u') tmp++;
	}
	if (tmp < 3) return 0;
	// One letter that appears twice in a row
	tmp = 0;
	for (i=0; i < (STRING_LEN-1); i++) {
		if (str[i] == str[i+1]) {
			tmp = 1;
			break; // Break out early to avoid further unnecessary checks
		}
	}
	if (tmp == 0) return 0;
	// Forbidden strings 'ab', 'cd', 'pq', 'xy'
	if (strstr(str, "ab")) return 0;
	if (strstr(str, "cd")) return 0;
	if (strstr(str, "pq")) return 0;
	if (strstr(str, "xy")) return 0;
	return 1;
}

int nicetwo(char *str) {
	char tmpstr[STRING_LEN];
	char needle[2];
	unsigned int i, j, tmp;
	// Doubled pair of letters, no overlap
	tmp = 0;
	for (i=0; i < (STRING_LEN-1); i++) {
		memcpy(tmpstr, str, sizeof(tmpstr)); // Make a copy of the string we're dealing with
		needle[0] = tmpstr[i];               // Go through every character pair in the string
		needle[1] = tmpstr[i+1];
		tmpstr[i] = 0;                       // Remove it from the string so it cannot be mistaken as overlap
		tmpstr[i+1] = 0;
		for (j=0; j < (STRING_LEN-1); j++) { // Search the string for the character pair now that the original is gone
			if (tmpstr[j] == needle[0] && tmpstr[j+1] == needle[1]) {
				tmp = 1;
				break;
			}
		}
		if (tmp > 1) break; // To break out of both loops
	}
	if (tmp == 0) return 0;
	// Double-letters with a letter in between
	tmp = 0;
	for (i=0; i < (STRING_LEN-2); i++) {
		if (str[i] == str[i+2]) {
			tmp = 1;
			break;
		}
	}
	if (tmp == 0) return 0;
	return 1;
}

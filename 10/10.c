#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_STRING "1321131112" // Puzzle Input

#define STRING_LEN 8*1024*1024 // 8 whole megabytes per string...good lord.

inline unsigned int ctoi(char);

int main(void) {
	char *string = malloc(STRING_LEN);
	char *tmpstring = malloc(STRING_LEN);
	strcpy(string, INITIAL_STRING);
	unsigned int i, j, num, count, pos, fortylen;
	for (i=0; i < 50; i++) {
		unsigned int len = strlen(string);
		num = ctoi(string[0]);
		count = 1;
		pos = 0;
		for (j=1; j <= len; j++) {
			if (ctoi(string[j]) == num) count++;
			else {
				pos += snprintf(&tmpstring[pos], sizeof(tmpstring), "%d%d", count, num);
				num = ctoi(string[j]);
				count = 1;
			}
		}
		strcpy(string, tmpstring);
		if (i == 39) fortylen = strlen(string);
	}
	printf("Part One Solution: %d\n", fortylen);
	printf("Part Two Solution: %d\n", (int)strlen(string));
	return EXIT_SUCCESS;
}

inline unsigned int ctoi(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	return 0;
}

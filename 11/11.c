#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD "hepxcrrq" // Puzzle Input
#define PASSLEN 8

int main(void) {
	char password[PASSLEN+1] = PASSWORD;
	char tmpstr[PASSLEN+1];
	char firstpass[PASSLEN+1];
	unsigned int i, j, done, first;
	done = 0;
	first = 1;
	while (1) {
		// "Increment" the password string
		for (i=(PASSLEN-1); i >= 0; i--) {
			password[i]++;
			// Skip any i, o, or l, as they are not allowed.
			if (password[i] == 'i' || password[i] == 'o' || password[i] == 'l') password[i]++;
			if (password[i] <= 'z') break;
			if (i == 0) {
				done = 1;
				break;
			}
			password[i] = 'a';
		}
		if (done) break;

		// Not sure if puzzle input will ever have 'i', 'o', or 'l', but just in case...
		unsigned int cont = 1;
		for (i=0; i < PASSLEN; i++) if (password[i] == 'i' || password[i] == 'o' || password[i] == 'l') cont = 0;
		if (!cont) continue;
		
		// Check for a rising straight of characters; i.e. 'abc', 'def', 'xyz'
		cont = 0;
		for (i=0; i < (PASSLEN-2); i++) {
			if (password[i+1] == (password[i]+1) && password[i+2] == (password[i]+2)) cont = 1;
		}
		if (!cont) continue;
		
		// Check for two unique, non-overlapping doubles of characters; i.e. 'aa' and 'bb', but not 'aaa'
		cont = 0;
		for (i=0; i < (PASSLEN-1); i++) {
			if (password[i] == password[i+1]) {
				strcpy(tmpstr, password);
				tmpstr[i] = 0; // Wipe this double from the string to check for non-overlapping
				tmpstr[i+1] = 1; // Ensure these values are different so the next loop doesn't recognize them
				for (j=0; j < (PASSLEN-1); j++) {
					if (tmpstr[j] == tmpstr[j+1] && tmpstr[j] != password[i]) cont = 1;
				}
			}
		}
		if (!cont) continue;
		
		// Keep the first password we generate as part one's solution
		if (first) {
			strcpy(firstpass, password);
			first = 0;
		}
		else break;
	}
	printf("Part One Solution: %s\n", firstpass);
	printf("Part Two Solution: %s\n", password);
	return EXIT_SUCCESS;
}

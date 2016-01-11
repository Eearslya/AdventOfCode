#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>

int main(void) {
	const char *secret = "iwrupvqb"; // Puzzle input
	unsigned char md5[MD5_DIGEST_LENGTH];
	char key[sizeof(secret)+16]; // Allow for a 16-digit integer just..because.
	unsigned int i = 1;
	unsigned int fivezeroes = 0;
	unsigned int sixzeroes = 0;
	while (1) {
		unsigned int len = snprintf(key, sizeof(key), "%s%u", secret, i);
		MD5((unsigned char*)key, len, md5);
		if (md5[0] == 0 && md5[1] == 0 && (md5[2] & 0xF0) == 0) {
			if (fivezeroes == 0) fivezeroes = i;
			if (md5[2] == 0 && sixzeroes == 0) sixzeroes = i;
			if (fivezeroes > 0 && sixzeroes > 0) break;
		}
		i++;
	}
	printf("Part One Solution: %d\n", fivezeroes);
	printf("Part Two Solution: %d\n", sixzeroes);
	return EXIT_SUCCESS;
}

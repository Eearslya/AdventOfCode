#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_array(json_t*, unsigned int);
int parse_object(json_t*, unsigned int);

int main(void) {
	FILE *input = fopen("input", "r");
	if (input == NULL) {
		printf("Could not open input file\n");
		exit(EXIT_FAILURE);
	}
	json_error_t json_err;
	json_t *json = json_loadf(input, 0, &json_err);
	if (!json) {
		printf("Error parsing JSON input!\nAt line %d, col %d: %s\n", json_err.line, json_err.column, json_err.text);
		exit(EXIT_FAILURE);
	}
	printf("Part One Solution: %d\n", parse_array(json, 1));
	printf("Part Two Solution: %d\n", parse_array(json, 2));
	json_decref(json);
	fclose(input);
	return EXIT_SUCCESS;
}

int parse_array(json_t *json, unsigned int part) {
	size_t i;
	json_t *tmp;
	int ret = 0;
	json_array_foreach(json, i, tmp) {
		if (json_is_array(tmp)) ret += parse_array(tmp, part);
		else if (json_is_object(tmp)) ret += parse_object(tmp, part);
		else if (json_is_number(tmp)) ret += (int) json_number_value(tmp);
	}
	return ret;
}

int parse_object(json_t *json, unsigned int part) {
	const char *key;
	json_t *tmp;
	int ret = 0;
	json_object_foreach(json, key, tmp) {
		if (json_is_array(tmp)) ret += parse_array(tmp, part);
		else if (json_is_object(tmp)) ret += parse_object(tmp, part);
		else if (json_is_number(tmp)) ret += (int) json_number_value(tmp);
		else if (json_is_string(tmp) && part == 2) {
			if (strcmp(json_string_value(tmp), "red") == 0) return 0;
		}
	}
	return ret;
}

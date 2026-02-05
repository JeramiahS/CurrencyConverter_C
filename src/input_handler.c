#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_handler.h"

void print_usage_instructions()
{
	puts("Usage: {AMOUNT} {FROM_CODE} {TO_CODE}");
}

bool is_valid_amount (const char *AMOUNT)
{
	char *end_ptr;
	const double CHECK_VALUE = strtof(AMOUNT, &end_ptr);
	if (CHECK_VALUE == 0 || strncmp(AMOUNT, end_ptr, sizeof(AMOUNT)) == 0) {
		fprintf(stderr, "First argument must be a non-zero numerical value.\n");
		exit(EXIT_FAILURE);
	}

	return true;
}

bool codes_are_three_chars (const char *FROM_CODE, const char *TO_CODE)
{
	const int MAX_CHECK_LENGTH = 4;
	if (strnlen(FROM_CODE, MAX_CHECK_LENGTH) != 3 || strnlen(TO_CODE, MAX_CHECK_LENGTH) != 3) {
		fprintf(stderr, "Currency codes must be exactly three characters long.\n");
		exit(EXIT_FAILURE);
	}

	return true;
}

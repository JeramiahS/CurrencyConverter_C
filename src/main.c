#include "input_handler.h"
#include "http_handler.h"

#include <stdlib.h>

int main (int argc, char *argv[])
{
	if (argc == 1) {
		print_usage_instructions();
		exit(EXIT_SUCCESS);
	}

	if (is_valid_amount(argv[1]) && codes_are_three_chars(argv[2], argv[3])) {
		print_conversion_result(argv);
	}

	return 0;
}

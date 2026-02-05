#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdbool.h>

void print_usage_instructions ();

//Returns true if the given string can be parsed as a float, otherwise false.
bool is_valid_amount (const char *);

//Returns true if both of the given strings are exactly three chars in length, otherwise false.
bool codes_are_three_chars (const char *, const char *);

#endif

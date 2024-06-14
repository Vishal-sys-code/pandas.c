#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

// Function to duplicate a string
char* strdup(const char *str);

// Function to trim leading and trailing whitespace from a string
char* strtrim(char *str);

// Function to split a string by a delimiter
char** strsplit(const char *str, char delimiter, size_t *num_tokens);

// Function to free the memory allocated by strsplit
void free_strsplit(char **tokens, size_t num_tokens);

#endif // UTILS_H
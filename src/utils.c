#include "utils.h"
#include <stdlib.h>
#include <string.h>

// Function to trim leading and trailing whitespace from a string
char* strtrim(const char *str) {
    size_t start = 0;
    size_t end = strlen(str) - 1;

    // Trim leading whitespace
    while (isspace((unsigned char)str[start])) {
        start++;
    }

    // Trim trailing whitespace
    while (end > start && isspace((unsigned char)str[end])) {
        end--;
    }

    // Null-terminate the trimmed string
    char *trimmed_str = strndup(str + start, end - start + 1);
    return trimmed_str;
}

// Function to split a string into tokens based on a delimiter
char** strsplit(const char *str, char delimiter, size_t *num_tokens) {
    size_t max_tokens = 64; // Initial guess for max tokens
    char **tokens = malloc(max_tokens * sizeof(char*));
    if (!tokens) return NULL;

    size_t count = 0;
    const char *start = str;
    const char *end = str;

    while (*end) {
        if (*end == delimiter) {
            // Found a token
            if (count >= max_tokens) {
                // Resize tokens array if needed
                max_tokens *= 2;
                char **new_tokens = realloc(tokens, max_tokens * sizeof(char*));
                if (!new_tokens) {
                    free_strsplit(tokens, count);
                    return NULL;
                }
                tokens = new_tokens;
            }

            // Allocate memory for the token
            size_t token_length = end - start;
            tokens[count] = malloc((token_length + 1) * sizeof(char));
            if (!tokens[count]) {
                free_strsplit(tokens, count);
                return NULL;
            }

            // Copy the token
            strncpy(tokens[count], start, token_length);
            tokens[count][token_length] = '\0';
            count++;

            // Move to the next token
            start = end + 1;
        }
        end++;
    }

    // Add the last token
    size_t token_length = end - start;
    tokens[count] = malloc((token_length + 1) * sizeof(char));
    if (!tokens[count]) {
        free_strsplit(tokens, count);
        return NULL;
    }
    strncpy(tokens[count], start, token_length);
    tokens[count][token_length] = '\0';
    count++;

    *num_tokens = count;
    return tokens;
}

// Function to free memory allocated by strsplit
void free_strsplit(char **tokens, size_t num_tokens) {
    if (!tokens) return;

    for (size_t i = 0; i < num_tokens; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
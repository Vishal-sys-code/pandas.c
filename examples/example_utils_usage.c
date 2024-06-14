#include "utils.h"
#include <stdio.h>

int main() {
    // Example usage of strtrim
    const char *str_with_spaces = "   Hello, world!   ";
    char *trimmed_str = strtrim(str_with_spaces);
    printf("Trimmed string: '%s'\n", trimmed_str);
    free(trimmed_str);

    // Example usage of strsplit
    const char *csv_line = "John,Doe,30";
    size_t num_tokens;
    char **tokens = strsplit(csv_line, ',', &num_tokens);
    if (!tokens) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    printf("Split tokens:\n");
    for (size_t i = 0; i < num_tokens; i++) {
        printf("[%zu]: %s\n", i, tokens[i]);
    }

    // Free memory allocated by strsplit
    free_strsplit(tokens, num_tokens);

    return 0;
}
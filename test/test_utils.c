#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Function declarations for test cases
void test_strtrim();
void test_strsplit();

// Main function to run all test cases
int main() {
    printf("Running Utils Tests...\n");

    test_strtrim();
    test_strsplit();

    printf("All tests completed.\n");

    return 0;
}

// Test case for strtrim function
void test_strtrim() {
    printf("Running test_strtrim...\n");

    const char *str_with_spaces = "   Hello, world!   ";
    char *trimmed_str = strtrim(str_with_spaces);
    if (!trimmed_str) {
        fprintf(stderr, "test_strtrim failed: Unable to trim string\n");
        return;
    }

    // Check the trimmed string
    const char *expected_trimmed_str = "Hello, world!";
    if (strcmp(trimmed_str, expected_trimmed_str) != 0) {
        fprintf(stderr, "test_strtrim failed: Trimmed string does not match expected\n");
        free(trimmed_str);
        return;
    }

    // Clean up
    free(trimmed_str);
    printf("test_strtrim passed.\n");
}

// Test case for strsplit function
void test_strsplit() {
    printf("Running test_strsplit...\n");

    const char *csv_line = "John,Doe,30";
    size_t num_tokens;
    char **tokens = strsplit(csv_line, ',', &num_tokens);
    if (!tokens) {
        fprintf(stderr, "test_strsplit failed: Unable to split string\n");
        return;
    }

    // Check number of tokens
    if (num_tokens != 3) {
        fprintf(stderr, "test_strsplit failed: Incorrect number of tokens\n");
        free_strsplit(tokens, num_tokens);
        return;
    }

    // Check token values
    const char *expected_tokens[] = {"John", "Doe", "30"};
    for (size_t i = 0; i < num_tokens; i++) {
        if (strcmp(tokens[i], expected_tokens[i]) != 0) {
            fprintf(stderr, "test_strsplit failed: Token value mismatch\n");
            free_strsplit(tokens, num_tokens);
            return;
        }
    }

    // Clean up
    free_strsplit(tokens, num_tokens);
    printf("test_strsplit passed.\n");
}
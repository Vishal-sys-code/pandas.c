#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/series.h"

// Function declarations for test cases
void test_create_delete_series();
void test_add_value();
void test_print_series();

// Main function to run all test cases
int main() {
    printf("Running Series Tests...\n");

    test_create_delete_series();
    test_add_value();
    test_print_series();

    printf("All tests completed.\n");

    return 0;
}

// Test case for creating and deleting a Series
void test_create_delete_series() {
    printf("Running test_create_delete_series...\n");

    // Create Series
    Series *series = create_series("TestSeries", DF_INT);
    if (!series) {
        fprintf(stderr, "test_create_delete_series failed: Unable to create Series\n");
        return;
    }

    // Check Series name and type
    if (strcmp(series->name, "TestSeries") != 0 || series->type != DF_INT) {
        fprintf(stderr, "test_create_delete_series failed: Series name or type does not match\n");
        delete_series(series);
        return;
    }

    // Delete Series
    delete_series(series);
    printf("test_create_delete_series passed.\n");
}

// Test case for adding values to a Series
void test_add_value() {
    printf("Running test_add_value...\n");

    // Create Series
    Series *int_series = create_series("Integers", DF_INT);
    if (!int_series) {
        fprintf(stderr, "test_add_value failed: Unable to create integer Series\n");
        return;
    }

    // Add values to integer Series
    SeriesValue value1 = {.i_val = 10};
    SeriesValue value2 = {.i_val = 20};
    SeriesValue value3 = {.i_val = 30};

    if (add_value(int_series, value1) != 0 || add_value(int_series, value2) != 0 || add_value(int_series, value3) != 0) {
        fprintf(stderr, "test_add_value failed: Unable to add value to integer Series\n");
        delete_series(int_series);
        return;
    }

    // Check number of values added
    if (int_series->size != 3) {
        fprintf(stderr, "test_add_value failed: Incorrect number of values added to Series\n");
        delete_series(int_series);
        return;
    }

    // Delete Series
    delete_series(int_series);
    printf("test_add_value passed.\n");
}

// Test case for printing a Series
void test_print_series() {
    printf("Running test_print_series...\n");

    // Create Series
    Series *str_series = create_series("Strings", DF_STRING);
    if (!str_series) {
        fprintf(stderr, "test_print_series failed: Unable to create string Series\n");
        return;
    }

    // Add values to string Series
    SeriesValue value1 = {.s_val = "Apple"};
    SeriesValue value2 = {.s_val = "Banana"};
    SeriesValue value3 = {.s_val = "Cherry"};

    add_value(str_series, value1);
    add_value(str_series, value2);
    add_value(str_series, value3);

    // Print string Series
    printf("Printing Series '%s':\n", str_series->name);
    print_series(str_series);

    // Delete Series
    delete_series(str_series);
    printf("test_print_series passed.\n");
}
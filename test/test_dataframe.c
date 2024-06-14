#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/dataframe.h"

// Function declarations for test cases
void test_create_delete_dataframe();
void test_add_row();
void test_print_dataframe();

// Main function to run all test cases
int main() {
    printf("Running DataFrame Tests...\n");

    test_create_delete_dataframe();
    test_add_row();
    test_print_dataframe();

    printf("All tests completed.\n");

    return 0;
}

// Test case for creating and deleting a DataFrame
void test_create_delete_dataframe() {
    printf("Running test_create_delete_dataframe...\n");

    // Define column names and types
    char *column_names[] = {"ID", "Name", "Age"};
    DataType column_types[] = {DF_INT, DF_STRING, DF_INT};

    // Create DataFrame
    DataFrame *df = create_dataframe(column_names, column_types, 3);
    if (!df) {
        fprintf(stderr, "test_create_delete_dataframe failed: Unable to create DataFrame\n");
        return;
    }

    // Check column names and types
    for (size_t i = 0; i < df->num_cols; i++) {
        if (strcmp(df->columns[i].name, column_names[i]) != 0) {
            fprintf(stderr, "test_create_delete_dataframe failed: Column names do not match\n");
            delete_dataframe(df);
            return;
        }
        if (df->columns[i].type != column_types[i]) {
            fprintf(stderr, "test_create_delete_dataframe failed: Column types do not match\n");
            delete_dataframe(df);
            return;
        }
    }

    // Delete DataFrame
    delete_dataframe(df);
    printf("test_create_delete_dataframe passed.\n");
}

// Test case for adding rows to a DataFrame
void test_add_row() {
    printf("Running test_add_row...\n");

    // Create DataFrame with predefined structure
    char *column_names[] = {"ID", "Name", "Age"};
    DataType column_types[] = {DF_INT, DF_STRING, DF_INT};
    DataFrame *df = create_dataframe(column_names, column_types, 3);
    if (!df) {
        fprintf(stderr, "test_add_row failed: Unable to create DataFrame\n");
        return;
    }

    // Add rows to the DataFrame
    SeriesValue row1[] = {{.i_val = 1}, {.s_val = "Alice"}, {.i_val = 30}};
    SeriesValue row2[] = {{.i_val = 2}, {.s_val = "Bob"}, {.i_val = 35}};
    SeriesValue row3[] = {{.i_val = 3}, {.s_val = "Charlie"}, {.i_val = 28}};

    if (add_row(df, row1) != 0 || add_row(df, row2) != 0 || add_row(df, row3) != 0) {
        fprintf(stderr, "test_add_row failed: Unable to add row to DataFrame\n");
        delete_dataframe(df);
        return;
    }

    // Check number of rows added
    if (df->columns[0].size != 3) {
        fprintf(stderr, "test_add_row failed: Incorrect number of rows added\n");
        delete_dataframe(df);
        return;
    }

    // Delete DataFrame
    delete_dataframe(df);
    printf("test_add_row passed.\n");
}

// Test case for printing a DataFrame
void test_print_dataframe() {
    printf("Running test_print_dataframe...\n");

    // Create DataFrame with predefined structure
    char *column_names[] = {"ID", "Name", "Age"};
    DataType column_types[] = {DF_INT, DF_STRING, DF_INT};
    DataFrame *df = create_dataframe(column_names, column_types, 3);
    if (!df) {
        fprintf(stderr, "test_print_dataframe failed: Unable to create DataFrame\n");
        return;
    }

    // Add rows to the DataFrame
    SeriesValue row1[] = {{.i_val = 1}, {.s_val = "Alice"}, {.i_val = 30}};
    SeriesValue row2[] = {{.i_val = 2}, {.s_val = "Bob"}, {.i_val = 35}};
    SeriesValue row3[] = {{.i_val = 3}, {.s_val = "Charlie"}, {.i_val = 28}};
    add_row(df, row1);
    add_row(df, row2);
    add_row(df, row3);

    // Print DataFrame
    printf("Printing DataFrame:\n");
    print_dataframe(df);

    // Delete DataFrame
    delete_dataframe(df);
    printf("test_print_dataframe passed.\n");
}
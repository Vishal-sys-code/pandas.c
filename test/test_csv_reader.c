#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_reader.h"
#include "dataframe.h"

// Function declarations for test cases
void test_read_csv_success();
void test_read_csv_failure();

// Function to compare two DataFrames for equality
int compare_dataframes(DataFrame *df1, DataFrame *df2) {
    if (df1->num_cols != df2->num_cols) return 0;

    for (size_t i = 0; i < df1->num_cols; i++) {
        if (strcmp(df1->columns[i].name, df2->columns[i].name) != 0) return 0;
        if (df1->columns[i].type != df2->columns[i].type) return 0;
        if (df1->columns[i].size != df2->columns[i].size) return 0;

        for (size_t j = 0; j < df1->columns[i].size; j++) {
            switch (df1->columns[i].type) {
                case DF_INT:
                    if (df1->columns[i].data[j].i_val != df2->columns[i].data[j].i_val) return 0;
                    break;
                case DF_FLOAT:
                    if (df1->columns[i].data[j].f_val != df2->columns[i].data[j].f_val) return 0;
                    break;
                case DF_STRING:
                    if (strcmp(df1->columns[i].data[j].s_val, df2->columns[i].data[j].s_val) != 0) return 0;
                    break;
            }
        }
    }

    return 1;
}

// Main function to run all test cases
int main() {
    printf("Running CSV Reader Tests...\n");

    test_read_csv_success();
    test_read_csv_failure();

    printf("All tests completed.\n");

    return 0;
}

// Test case for successful CSV reading
void test_read_csv_success() {
    printf("Running test_read_csv_success...\n");

    const char *filename = "tests/test_data_success.csv";

    // Define expected DataFrame
    char *column_names[] = {"ID", "Name", "Age"};
    DataType column_types[] = {DF_INT, DF_STRING, DF_INT};

    DataFrame *expected_df = create_dataframe(column_names, column_types, 3);
    add_row(expected_df, (SeriesValue[]){{.i_val = 1}, {.s_val = "Alice"}, {.i_val = 30}});
    add_row(expected_df, (SeriesValue[]){{.i_val = 2}, {.s_val = "Bob"}, {.i_val = 35}});
    add_row(expected_df, (SeriesValue[]){{.i_val = 3}, {.s_val = "Charlie"}, {.i_val = 28}});

    // Read CSV file into DataFrame
    DataFrame *actual_df = pandas_read_csv(filename);
    if (!actual_df) {
        fprintf(stderr, "test_read_csv_success failed: Unable to read CSV file %s\n", filename);
        delete_dataframe(expected_df);
        return;
    }

    // Compare DataFrames
    if (compare_dataframes(expected_df, actual_df)) {
        printf("test_read_csv_success passed.\n");
    } else {
        fprintf(stderr, "test_read_csv_success failed: DataFrames do not match.\n");
    }

    // Clean up
    delete_dataframe(expected_df);
    delete_dataframe(actual_df);
}

// Test case for failing CSV reading
void test_read_csv_failure() {
    printf("Running test_read_csv_failure...\n");

    const char *filename = "tests/test_data_failure.csv";

    // Read CSV file into DataFrame
    DataFrame *df = pandas_read_csv(filename);
    if (df) {
        fprintf(stderr, "test_read_csv_failure failed: Expected failure reading CSV file %s\n", filename);
        delete_dataframe(df);
    } else {
        printf("test_read_csv_failure passed.\n");
    }
}
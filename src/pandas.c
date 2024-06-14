#include "pandas.h"
#include "csv_reader.h"
#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>

// Function to read a CSV file into a DataFrame
DataFrame* pandas_read_csv(const char *filename) {
    CSVOptions options = csv_get_default_options();
    DataFrame *df = NULL;
    CSVStatus status = read_csv(filename, options, &df);

    if (status != CSV_SUCCESS) {
        fprintf(stderr, "Error reading CSV file: %s\n", filename);
        return NULL;
    }

    return df;
}

// Function to delete a DataFrame
void pandas_delete_dataframe(DataFrame *df) {
    delete_dataframe(df);
}

// Function to print a DataFrame
void pandas_print_dataframe(const DataFrame *df) {
    print_dataframe(df);
}
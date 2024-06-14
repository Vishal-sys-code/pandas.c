#include "pandas.h"
#include <stdio.h>

int main() {
    // Read CSV file into DataFrame
    DataFrame *df = pandas_read_csv("data.csv");
    if (!df) {
        fprintf(stderr, "Failed to read CSV file\n");
        return 1;
    }

    // Print DataFrame
    pandas_print_dataframe(df);

    // Clean up
    pandas_delete_dataframe(df);
    return 0;
}

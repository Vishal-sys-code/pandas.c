#include "dataframe.h"
#include <stdio.h>

int main() {
    // Define column names and types
    char *column_names[] = {"ID", "Name", "Score"};
    DataType column_types[] = {DF_INT, DF_STRING, DF_FLOAT};

    // Create DataFrame
    DataFrame *df = create_dataframe(column_names, column_types, 3);
    if (!df) {
        fprintf(stderr, "Failed to create DataFrame\n");
        return 1;
    }

    // Add rows
    SeriesValue row1[] = {{.i_val = 1}, {.s_val = "Alice"}, {.f_val = 95.5}};
    SeriesValue row2[] = {{.i_val = 2}, {.s_val = "Bob"}, {.f_val = 89.0}};
    SeriesValue row3[] = {{.i_val = 3}, {.s_val = "Charlie"}, {.f_val = 92.3}};
    
    if (add_row(df, row1) != 0 || add_row(df, row2) != 0 || add_row(df, row3) != 0) {
        fprintf(stderr, "Failed to add row to DataFrame\n");
        delete_dataframe(df);
        return 1;
    }

    // Print DataFrame
    print_dataframe(df);

    // Clean up
    delete_dataframe(df);
    return 0;
}
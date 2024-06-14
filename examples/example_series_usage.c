#include "series.h"
#include <stdio.h>
#include <dataframe.h>

int main() {
    // Create Series
    Series *int_series = create_series("Integers", DF_INT);
    if (!int_series) {
        fprintf(stderr, "Failed to create integer Series\n");
        return 1;
    }

    // Add values to integer Series
    SeriesValue value1 = {.i_val = 10};
    SeriesValue value2 = {.i_val = 20};
    SeriesValue value3 = {.i_val = 30};

    if (add_value(int_series, value1) != 0 || add_value(int_series, value2) != 0 || add_value(int_series, value3) != 0) {
        fprintf(stderr, "Failed to add value to integer Series\n");
        delete_series(int_series);
        return 1;
    }

    // Print integer Series
    print_series(int_series);

    // Clean up
    delete_series(int_series);
    return 0;
}
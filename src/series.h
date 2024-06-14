#ifndef SERIES_H
#define SERIES_H

#include <stddef.h>

// Data types that can be held in the Series
typedef enum {
    SERIES_INT,
    SERIES_FLOAT,
    SERIES_STRING
} SeriesType;

// Union to hold different types of values in the Series
typedef union {
    int i_val;
    float f_val;
    char *s_val;
} SeriesValue;

// Structure to represent a Series
typedef struct {
    char *name;       // Series name
    SeriesType type;  // Data type of the Series
    SeriesValue *data;  // Pointer to the data
    size_t size;      // Number of elements in the Series
} Series;

// Function to create a Series
Series* create_series(const char *name, SeriesType type);

// Function to delete a Series and free memory
void delete_series(Series *series);

// Function to add a value to the Series
int add_value(Series *series, SeriesValue value);

// Function to print the Series
void print_series(const Series *series);

#endif // SERIES_H
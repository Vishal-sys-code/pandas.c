#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <stddef.h>

// Data types that can be held in the DataFrame
typedef enum {
    DF_INT,
    DF_FLOAT,
    DF_STRING
} DataType;

// Union to hold different types of values in the DataFrame
typedef union {
    int i_val;
    float f_val;
    char *s_val;
} SeriesValue;

// Structure to represent a Series (column)
typedef struct {
    char *name;        // Series name
    DataType type;     // Data type of the Series
    SeriesValue *data; // Pointer to the data
    size_t size;       // Number of elements in the Series
} Series;

// Structure to represent a DataFrame
typedef struct {
    Series *columns; // Array of Series (columns)
    size_t num_cols; // Number of columns
} DataFrame;

// Function to create a DataFrame
DataFrame* create_dataframe(char **column_names, DataType *types, size_t num_cols);

// Function to delete a DataFrame and free memory
void delete_dataframe(DataFrame *df);

// Function to add a row to the DataFrame
int add_row(DataFrame *df, SeriesValue *row_data);

// Function to print the DataFrame
void print_dataframe(const DataFrame *df);

#endif // DATAFRAME_H
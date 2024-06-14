#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <stddef.h>

// Data types that can be held in the DataFrame
typedef enum {
    DF_INT,
    DF_FLOAT,
    DF_STRING
} DataType;

// Generic data holder for different types of data
typedef union {
    int i_val;
    float f_val;
    char *s_val;
} DataValue;

// Structure to represent a DataFrame column
typedef struct {
    char *name;       // Column name
    DataType type;    // Data type of the column
    DataValue *data;  // Pointer to the data
} DataFrameColumn;

// Structure to represent a DataFrame
typedef struct {
    DataFrameColumn *columns; // Array of columns
    size_t num_cols;          // Number of columns
    size_t num_rows;          // Number of rows
} DataFrame;

// Function to create a DataFrame
DataFrame* create_dataframe(char **column_names, DataType *types, size_t num_cols);

// Function to delete a DataFrame and free memory
void delete_dataframe(DataFrame *df);

// Function to add a row to the DataFrame
int add_row(DataFrame *df, DataValue *row_data);

// Function to print the DataFrame
void print_dataframe(const DataFrame *df);

#endif // DATAFRAME_H
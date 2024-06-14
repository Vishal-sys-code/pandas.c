#ifndef PANDAS_H
#define PANDAS_H

#include "dataframe.h"
#include "csv_reader.h"

// Main library interface for users
// Functions for creating, manipulating, and managing DataFrames

// Function to create an empty DataFrame with specified columns
DataFrame* pandas_create_empty(char **column_names, DataType *types, size_t num_cols);

// Function to read a CSV file into a DataFrame with default options
CSVStatus pandas_read_csv(const char *filename, DataFrame **out_df);

// Function to read a CSV file into a DataFrame with specified options
CSVStatus pandas_read_csv_with_options(const char *filename, CSVOptions options, DataFrame **out_df);

// Function to print a DataFrame
void pandas_print_dataframe(const DataFrame *df);

// Function to free a DataFrame
void pandas_free_dataframe(DataFrame *df);

#endif // PANDAS_H
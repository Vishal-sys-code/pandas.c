#ifndef PANDAS_H
#define PANDAS_H

#include "dataframe.h"

// Function to read a CSV file into a DataFrame
DataFrame* pandas_read_csv(const char *filename);

// Function to delete a DataFrame
void pandas_delete_dataframe(DataFrame *df);

// Function to print a DataFrame
void pandas_print_dataframe(const DataFrame *df);

#endif // PANDAS_H
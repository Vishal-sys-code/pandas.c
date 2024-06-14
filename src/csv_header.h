#ifndef CSV_READER_H
#define CSV_READER_H

#include "dataframe.h"
#include <stddef.h>

// Enum for possible CSV parsing errors
typedef enum {
    CSV_SUCCESS,
    CSV_FILE_NOT_FOUND,
    CSV_MEMORY_ERROR,
    CSV_PARSE_ERROR
} CSVStatus;

// Structure to hold CSV parsing options
typedef struct {
    char delimiter;
    int has_header;
} CSVOptions;

// Function to initialize default CSV options
CSVOptions csv_get_default_options();

// Function to read a CSV file into a DataFrame
CSVStatus read_csv(const char *filename, CSVOptions options, DataFrame **out_df);

// Function to free memory allocated by DataFrame created by read_csv
void free_csv_dataframe(DataFrame *df);

#endif // CSV_READER_H
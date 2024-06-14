#include "csv_reader.h"
#include "dataframe.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Default options for CSV reading
CSVOptions csv_get_default_options() {
    CSVOptions options;
    options.delimiter = ',';
    return options;
}

// Internal function to parse a single line of CSV
static int parse_csv_line(const char *line, CSVOptions options, DataFrame *df) {
    size_t num_cols = df->num_cols;
    SeriesValue row_data[num_cols];

    char *mutable_line = strdup(line);
    if (!mutable_line) return -1;

    char *token = strtok(mutable_line, &options.delimiter);
    size_t col_idx = 0;

    while (token && col_idx < num_cols) {
        char *trimmed_token = strtrim(token);

        switch (df->columns[col_idx].type) {
            case DF_INT:
                row_data[col_idx].i_val = atoi(trimmed_token);
                break;
            case DF_FLOAT:
                row_data[col_idx].f_val = atof(trimmed_token);
                break;
            case DF_STRING:
                row_data[col_idx].s_val = strdup(trimmed_token);
                if (!row_data[col_idx].s_val) {
                    free(mutable_line);
                    return -1;
                }
                break;
        }

        token = strtok(NULL, &options.delimiter);
        col_idx++;
    }

    free(mutable_line);
    if (col_idx != num_cols) return -1;

    return add_row(df, row_data);
}

// Function to read a CSV file into a DataFrame
CSVStatus read_csv(const char *filename, CSVOptions options, DataFrame **out_df) {
    FILE *file = fopen(filename, "r");
    if (!file) return CSV_FILE_NOT_FOUND;

    char line[1024];
    char **column_names = NULL;
    DataType *column_types = NULL;
    size_t num_cols = 0;

    // Read the first line (header)
    if (fgets(line, sizeof(line), file)) {
        size_t num_tokens;
        char **tokens = strsplit(line, options.delimiter, &num_tokens);
        column_names = tokens;
        num_cols = num_tokens;
    } else {
        fclose(file);
        return CSV_PARSE_ERROR;
    }

    // Assuming types for this example, in real case this should be inferred or specified
    column_types = malloc(num_cols * sizeof(DataType));
    if (!column_types) {
        fclose(file);
        free_strsplit(column_names, num_cols);
        return CSV_MEMORY_ERROR;
    }

    for (size_t i = 0; i < num_cols; i++) {
        column_types[i] = DF_STRING; // Default to string, should be inferred or provided
    }

    DataFrame *df = create_dataframe(column_names, column_types, num_cols);
    if (!df) {
        fclose(file);
        free_strsplit(column_names, num_cols);
        free(column_types);
        return CSV_MEMORY_ERROR;
    }

    // Read the rest of the lines (data)
    while (fgets(line, sizeof(line), file)) {
        if (parse_csv_line(line, options, df) != 0) {
            fclose(file);
            delete_dataframe(df);
            free_strsplit(column_names, num_cols);
            free(column_types);
            return CSV_PARSE_ERROR;
        }
    }

    fclose(file);
    free_strsplit(column_names, num_cols);
    free(column_types);

    *out_df = df;
    return CSV_SUCCESS;
}
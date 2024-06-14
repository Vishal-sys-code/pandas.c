#include "dataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a DataFrame
DataFrame* create_dataframe(char **column_names, DataType *types, size_t num_cols) {
    DataFrame *df = malloc(sizeof(DataFrame));
    if (!df) return NULL;

    df->columns = malloc(num_cols * sizeof(Series));
    if (!df->columns) {
        free(df);
        return NULL;
    }

    for (size_t i = 0; i < num_cols; i++) {
        df->columns[i].name = strdup(column_names[i]);
        df->columns[i].type = types[i];
        df->columns[i].data = NULL;
        df->columns[i].size = 0;
    }

    df->num_cols = num_cols;
    return df;
}

// Function to delete a DataFrame and free memory
void delete_dataframe(DataFrame *df) {
    if (!df) return;

    for (size_t i = 0; i < df->num_cols; i++) {
        free(df->columns[i].name);
        if (df->columns[i].type == DF_STRING) {
            for (size_t j = 0; j < df->columns[i].size; j++) {
                free(df->columns[i].data[j].s_val);
            }
        }
        free(df->columns[i].data);
    }

    free(df->columns);
    free(df);
}

// Function to add a row to the DataFrame
int add_row(DataFrame *df, SeriesValue *row_data) {
    for (size_t i = 0; i < df->num_cols; i++) {
        Series *series = &df->columns[i];
        SeriesValue *new_data = realloc(series->data, (series->size + 1) * sizeof(SeriesValue));
        if (!new_data) return -1;

        series->data = new_data;
        switch (series->type) {
            case DF_INT:
                series->data[series->size].i_val = row_data[i].i_val;
                break;
            case DF_FLOAT:
                series->data[series->size].f_val = row_data[i].f_val;
                break;
            case DF_STRING:
                series->data[series->size].s_val = strdup(row_data[i].s_val);
                if (!series->data[series->size].s_val) return -1;
                break;
        }

        series->size++;
    }

    return 0;
}

// Function to print the DataFrame
void print_dataframe(const DataFrame *df) {
    // Print column headers
    for (size_t i = 0; i < df->num_cols; i++) {
        printf("%s\t", df->columns[i].name);
    }
    printf("\n");

    // Print row data
    size_t num_rows = df->columns[0].size;
    for (size_t row = 0; row < num_rows; row++) {
        for (size_t col = 0; col < df->num_cols; col++) {
            Series *series = &df->columns[col];
            switch (series->type) {
                case DF_INT:
                    printf("%d\t", series->data[row].i_val);
                    break;
                case DF_FLOAT:
                    printf("%f\t", series->data[row].f_val);
                    break;
                case DF_STRING:
                    printf("%s\t", series->data[row].s_val);
                    break;
            }
        }
        printf("\n");
    }
}
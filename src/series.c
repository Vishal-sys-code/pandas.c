#include "series.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataframe.h"

// Function to create a Series
Series* create_series(const char *name, DataType type) {
    Series *series = malloc(sizeof(Series));
    if (!series) return NULL;

    series->name = strdup(name);
    series->type = type;
    series->data = NULL;
    series->size = 0;

    return series;
}

// Function to delete a Series
void delete_series(Series *series) {
    if (!series) return;

    free(series->name);
    if (series->type == DF_STRING) {
        for (size_t i = 0; i < series->size; i++) {
            free(series->data[i].s_val);
        }
    }
    free(series->data);
    free(series);
}

// Function to add a value to a Series
int add_value(Series *series, SeriesValue value) {
    SeriesValue *new_data = realloc(series->data, (series->size + 1) * sizeof(SeriesValue));
    if (!new_data) return -1;

    series->data = new_data;
    switch (series->type) {
        case DF_INT:
            series->data[series->size].i_val = value.i_val;
            break;
        case DF_FLOAT:
            series->data[series->size].f_val = value.f_val;
            break;
        case DF_STRING:
            series->data[series->size].s_val = strdup(value.s_val);
            if (!series->data[series->size].s_val) return -1;
            break;
    }

    series->size++;
    return 0;
}

// Function to print a Series
void print_series(const Series *series) {
    printf("Series '%s' (type: %d):\n", series->name, series->type);
    for (size_t i = 0; i < series->size; i++) {
        switch (series->type) {
            case DF_INT:
                printf("%d\n", series->data[i].i_val);
                break;
            case DF_FLOAT:
                printf("%f\n", series->data[i].f_val);
                break;
            case DF_STRING:
                printf("%s\n", series->data[i].s_val);
                break;
        }
    }
}
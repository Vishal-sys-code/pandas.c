# Makefile for compiling and running tests

# Compiler options
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Source files and headers
SOURCES_CSV_READER = csv_reader.c dataframe.c series.c utils.c
SOURCES_DATAFRAME = dataframe.c series.c utils.c
SOURCES_SERIES = series.c utils.c
SOURCES_UTILS = utils.c

# Executables
TARGET_CSV_READER = test_csv_reader
TARGET_DATAFRAME = test_dataframe
TARGET_SERIES = test_series
TARGET_UTILS = test_utils

# Targets
all: $(TARGET_CSV_READER) $(TARGET_DATAFRAME) $(TARGET_SERIES) $(TARGET_UTILS)

$(TARGET_CSV_READER): test_csv_reader.c $(SOURCES_CSV_READER)
    $(CC) $(CFLAGS) -o $@ $^

$(TARGET_DATAFRAME): test_dataframe.c $(SOURCES_DATAFRAME)
    $(CC) $(CFLAGS) -o $@ $^

$(TARGET_SERIES): test_series.c $(SOURCES_SERIES)
    $(CC) $(CFLAGS) -o $@ $^

$(TARGET_UTILS): test_utils.c $(SOURCES_UTILS)
    $(CC) $(CFLAGS) -o $@ $^

# Clean
clean:
    rm -f $(TARGET_CSV_READER) $(TARGET_DATAFRAME) $(TARGET_SERIES) $(TARGET_UTILS)
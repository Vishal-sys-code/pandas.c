# Makefile for compiling and running tests

# Compiler options
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
INCLUDES = -I./include

# Directories
SRC_DIR = ./src
TEST_DIR = ./tests
BUILD_DIR = ./build

# Source files and headers
SOURCES_CSV_READER = $(SRC_DIR)/csv_reader.c $(SRC_DIR)/dataframe.c $(SRC_DIR)/series.c $(SRC_DIR)/utils.c
SOURCES_DATAFRAME = $(SRC_DIR)/dataframe.c $(SRC_DIR)/series.c $(SRC_DIR)/utils.c
SOURCES_SERIES = $(SRC_DIR)/series.c $(SRC_DIR)/utils.c
SOURCES_UTILS = $(SRC_DIR)/utils.c

# Executables
TARGET_CSV_READER = $(BUILD_DIR)/test_csv_reader
TARGET_DATAFRAME = $(BUILD_DIR)/test_dataframe
TARGET_SERIES = $(BUILD_DIR)/test_series
TARGET_UTILS = $(BUILD_DIR)/test_utils

# Default target
all: build $(TARGET_CSV_READER) $(TARGET_DATAFRAME) $(TARGET_SERIES) $(TARGET_UTILS)

# Create build directory
build:
	mkdir -p $(BUILD_DIR)

# Compile targets
$(TARGET_CSV_READER): $(TEST_DIR)/test_csv_reader.c $(SOURCES_CSV_READER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(TARGET_DATAFRAME): $(TEST_DIR)/test_dataframe.c $(SOURCES_DATAFRAME)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(TARGET_SERIES): $(TEST_DIR)/test_series.c $(SOURCES_SERIES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(TARGET_UTILS): $(TEST_DIR)/test_utils.c $(SOURCES_UTILS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all build clean
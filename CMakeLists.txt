# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

# Set the project name and language
project(MyProject C)

# Specify the C compiler manually if not detected automatically
if(NOT CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER "gcc")  # Adjust to your compiler executable name
endif()

# Compiler options
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# Directories (adjust paths as needed)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Source files (adjust as needed)
set(SOURCES_CSV_READER
    ${SRC_DIR}/csv_reader.c
    ${SRC_DIR}/dataframe.c
    ${SRC_DIR}/series.c
    ${SRC_DIR}/utils.c
)

set(SOURCES_DATAFRAME
    ${SRC_DIR}/dataframe.c
    ${SRC_DIR}/series.c
    ${SRC_DIR}/utils.c
)

set(SOURCES_SERIES
    ${SRC_DIR}/series.c
    ${SRC_DIR}/utils.c
)

set(SOURCES_UTILS
    ${SRC_DIR}/utils.c
)

# Executable targets
add_executable(test_csv_reader ${TEST_DIR}/test_csv_reader.c ${SOURCES_CSV_READER})
add_executable(test_dataframe ${TEST_DIR}/test_dataframe.c ${SOURCES_DATAFRAME})
add_executable(test_series ${TEST_DIR}/test_series.c ${SOURCES_SERIES})
add_executable(test_utils ${TEST_DIR}/test_utils.c ${SOURCES_UTILS})

# Include directories
target_include_directories(test_csv_reader PRIVATE ${INCLUDE_DIR})
target_include_directories(test_dataframe PRIVATE ${INCLUDE_DIR})
target_include_directories(test_series PRIVATE ${INCLUDE_DIR})
target_include_directories(test_utils PRIVATE ${INCLUDE_DIR})

# Set output directories
set_target_properties(test_csv_reader test_dataframe test_series test_utils
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
)

# Clean target
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/cmake/clean-all.cmake
)

# Add dependencies and tests here if needed
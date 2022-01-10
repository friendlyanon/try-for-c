cmake_minimum_required(VERSION 3.7)

project(TryForCTest C)

enable_testing()

find_package(TryForC 1 REQUIRED CONFIG)

add_executable(int_test int_test.c)
generate_try_for_c(
    ERROR_TYPE int
    OK_VALUE 0
    FILE_NAME int_test/try.h
)
target_include_directories(int_test PRIVATE "${PROJECT_BINARY_DIR}/int_test")

add_test(NAME try_for_c.int COMMAND int_test CONFIGURATIONS Debug)

add_executable(enum_test enum_test.c try_int_to_enum.c)
generate_try_for_c(
    ERROR_TYPE "enum error_enum"
    OK_VALUE ERROR_OK
    HEADERS error_codes.h
    FILE_NAME enum_test/try.h
    CUSTOM_CONTENT "TRY_ERROR_TYPE try_int_to_enum(int error);"
)
target_include_directories(
    enum_test PRIVATE
    "${PROJECT_BINARY_DIR}/enum_test"
    "${PROJECT_SOURCE_DIR}"
)

add_test(NAME try_for_c.enum COMMAND enum_test CONFIGURATIONS Debug)

add_executable(multiple_int_test multiple_int_test.c)
generate_try_for_c(
    ERROR_TYPE int
    OK_VALUE 0
    FILE_NAME multiple_int_test/try.h
)
target_include_directories(
    multiple_int_test PRIVATE
    "${PROJECT_BINARY_DIR}/multiple_int_test"
)

add_test(NAME try_for_c.multi COMMAND multiple_int_test CONFIGURATIONS Debug)

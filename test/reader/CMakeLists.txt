cmake_minimum_required(VERSION 3.20)

add_executable(reader-test reader_test.cpp)
target_link_libraries(reader-test sound_utils)

add_test(
    NAME reader
    COMMAND $<TARGET_FILE:reader-test>
    )

# run with: ctest -L lib
set_property(
    TEST reader
    PROPERTY LABELS lib reader
    )
cmake_minimum_required(VERSION 3.16)

add_executable(reader-test reader_test.cpp)
target_link_libraries(reader-test ${PROJECT_NAME})

# prepared necessary files for test
add_custom_command(
    TARGET reader-test
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy ${CMAKE_CURRENT_SOURCE_DIR}/test.txt
            $<TARGET_FILE_DIR:reader-test>)

add_custom_command(
    TARGET reader-test
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy ${CMAKE_CURRENT_SOURCE_DIR}/test.wav
            $<TARGET_FILE_DIR:reader-test>)

add_test(
    NAME reader-test_open_file
    COMMAND $<TARGET_FILE:reader-test> open_file
    )
    set_property(
        TEST reader-test_open_file
        PROPERTY LABELS reader-test reader-test_open_file
        )

add_test(
    NAME reader-test_read_wav
    COMMAND $<TARGET_FILE:reader-test> read_wav
    )
    set_property(
        TEST reader-test_read_wav
        PROPERTY LABELS reader-test reader-test_read_wav
        )
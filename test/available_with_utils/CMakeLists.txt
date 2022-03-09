cmake_minimum_required(VERSION 3.16)

add_executable(utils-available-test utils_available_test.cpp)
target_link_libraries(utils-available-test ${PROJECT_NAME})

# prepared necessary files for test
add_custom_command(
    TARGET utils-available-test
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy ${CMAKE_CURRENT_SOURCE_DIR}/test.txt
            $<TARGET_FILE_DIR:utils-available-test>)

add_test(
    NAME utils-available-test_split_string
    COMMAND $<TARGET_FILE:utils-available-test> split_string
    )
    set_property(
        TEST utils-available-test_split_string
        PROPERTY LABELS utils-available-test
        )
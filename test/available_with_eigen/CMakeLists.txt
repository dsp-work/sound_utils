cmake_minimum_required(VERSION 3.16)

add_executable(eigen-available-test with_eigen.cpp)
target_link_libraries(eigen-available-test ${PROJECT_NAME})

add_test(
    NAME eigen-available-test_intro1
    COMMAND $<TARGET_FILE:eigen-available-test> intro1
    )
    set_property(
        TEST eigen-available-test_intro1
        PROPERTY LABELS eigen-available-test eigen-available-test_intro1
        )

add_test(
    NAME eigen-available-test_intro2_1
    COMMAND $<TARGET_FILE:eigen-available-test> intro2_1
    )
    set_property(
        TEST eigen-available-test_intro2_1
        PROPERTY LABELS eigen-available-test eigen-available-test_intro2_1
        )

add_test(
    NAME eigen-available-test_intro2_2
    COMMAND $<TARGET_FILE:eigen-available-test> intro2_2
    )
    set_property(
        TEST eigen-available-test_intro2_2
        PROPERTY LABELS eigen-available-test eigen-available-test_intro2_2
        )
cmake_minimum_required(VERSION 3.16)

add_library(${PROJECT_NAME}-reader reader.cpp)
	target_link_libraries(${PROJECT_NAME}-reader ${PROJECT_NAME}-include)

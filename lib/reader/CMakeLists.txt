cmake_minimum_required(VERSION 3.16)

add_library(${PROJECT_NAME}-reader reader.cpp)
	target_include_directories(${PROJECT_NAME}-reader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
cmake_minimum_required(VERSION 3.16)

add_library(${PROJECT_NAME}-include INTERFACE)
	target_include_directories(${PROJECT_NAME}-include INTERFACE .)
	target_sources(${PROJECT_NAME}-include INTERFACE reader.hpp)
	target_link_libraries(${PROJECT_NAME}-include INTERFACE DspWork::Utils)
	target_link_libraries(${PROJECT_NAME}-include INTERFACE Eigen3::Eigen)
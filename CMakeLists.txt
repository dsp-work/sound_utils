cmake_minimum_required(VERSION 3.16)

# project name
project(sound_utils CXX)

#--------------- CMake compile config ------------------------------
include(./.cmake/cxx_config.cmake)

#----------------- clang-format config -------------------------
include(./.cmake/clang-format.cmake)

#----------------- Eigen install script --------------------------
include(./.cmake/eigen_install.cmake)

# ---------- dependencies ----------
include(./.cmake/dependency_eigen.cmake)
include(./.cmake/dependency_dsp_work_utils.cmake)


#------------------ build source config ------------------

# sub directories
add_subdirectory(lib)

# libraries
add_library(${PROJECT_NAME} INTERFACE)
  target_link_libraries(${PROJECT_NAME} INTERFACE dsp_work_utils::utils)
  target_link_libraries(${PROJECT_NAME} INTERFACE Eigen3::Eigen)
  # if want to add libraries...
  # target_link_libraries(${PROJECT_NAME} INTERFACE ${PROJECT_NAME}-tool_name)

# include path
target_include_directories(${PROJECT_NAME} INTERFACE include)

# for development executable(optional activate)
option(DEVELOP_EXECUTABLE_${PROJECT_NAME} "Build develop executable file on sound utils package" OFF)
if(DEVELOP_EXECUTABLE_${PROJECT_NAME})
# executables
    add_executable(develop_main develop_main.cpp)
    target_link_libraries(develop_main ${PROJECT_NAME})
endif()

# tests
option(${PROJECT_NAME}-with-test "Enable creation of tests." ON)
if(${PROJECT_NAME}-with-test)
  enable_testing()
  add_subdirectory(test)
endif()
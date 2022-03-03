cmake_minimum_required(VERSION 3.16)

# project name
project(sound_utils CXX)

#--------------- CMake compile config ------------------------------
enable_language(CXX)
set(CMAKE_CXX_STANDARD 11) # C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wendif-labels -Wfloat-equal -Winit-self -Winline -Wmissing-include-dirs -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-promo -Wswitch-default -Wswitch-enum -Wvariadic-macros -Wwrite-strings ")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=native")
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")
        set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-pg")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -pg")
        set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "-pg")
endif(CMAKE_COMPILER_IS_GNUCXX)

#----------------- clang-format config -------------------------
find_program(CLANG_FORMAT_EXE clang-format)

file(GLOB_RECURSE project_sources CONFIGURE_DEPENDS "[a-zA-Z]*.cpp" "[a-zA-Z]*.hpp")
list(FILTER project_sources EXCLUDE REGEX "build/*")

# add build target (clang-format lints)
# In use,
# `cmake --build . --target ${PROJECT_NAME}-format --verbose`
add_custom_target("${PROJECT_NAME}-format"
  COMMAND ${CLANG_FORMAT_EXE} --style=file --dry-run ${project_sources}
  COMMENT "Running clang-format(lints)"
  VERBATIM
  )

# add build target (clang-format warning overwrite)
# In use,
# `cmake --build . --target ${PROJECT_NAME}-format-fix`
add_custom_target("${PROJECT_NAME}-format-fix"
  COMMAND ${CLANG_FORMAT_EXE} --style=file -i ${project_sources}
  COMMENT "Running clang-format(overwrite)"
  VERBATIM
  )

if(CMAKE_COMPILER_IS_GNUCXX)
add_custom_target( "${PROJECT_NAME}-install-eigen"
  COMMAND git clone https://gitlab.com/libeigen/eigen.git ${PROJECT_SOURCE_DIR}/temp/eigen -b 3.4.0
  COMMAND cmake -DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/external -B ${PROJECT_SOURCE_DIR}/temp/eigen/build -G "MinGW Makefiles" ${PROJECT_SOURCE_DIR}/temp/eigen
  COMMAND cmake --install ${PROJECT_SOURCE_DIR}/temp/eigen/build
  COMMAND file(REMOVE_RECURSE ${PROJECT_SOURCE_DIR}/temp)
  VERBATIM
  )
else()
add_custom_target( "${PROJECT_NAME}-install-eigen"
  COMMAND git clone https://gitlab.com/libeigen/eigen.git ${PROJECT_SOURCE_DIR}/temp/eigen -b 3.4.0
  COMMAND cmake -DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/external -B ${PROJECT_SOURCE_DIR}/temp/eigen/build ${PROJECT_SOURCE_DIR}/temp/eigen
  COMMAND cmake install ${PROJECT_SOURCE_DIR}/temp/eigen/build
  COMMAND rm temp
  VERBATIM
  )
endif(CMAKE_COMPILER_IS_GNUCXX)


# ---------- dependencies ----------
set(BUILD_TESTING OFF CACHE BOOL "build flag of test for Eigen3" FORCE)
find_package(Eigen3 NO_MODULE)
if (Eigen3_FOUND)
  message(STATUS "Eigen3 is found!")
else() # 見つからない場合には自動インストール
  message(STATUS "Eigen3 is not found!")

  option(${PROJECT_NAME}-auto-install-eigen3 "Enable auto installing of eigen3." ON)
  if(${PROJECT_NAME}-auto-install-eigen3)
    message(STATUS "Start auto installing Eigen3...")
    message(STATUS "-- If you want not to install eigen3 automatically, Configure with `-D${PROJECT_NAME}-auto-install-eigen3=OFF`.")
    include(FetchContent)
    FetchContent_Declare(
      Eigen3
      GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
      GIT_TAG 3.4.0
    )
    FetchContent_MakeAvailable(eigen3)
  else()
    message(STATUS "Please install Eigen3 your self.")
  endif()

  find_package(Eigen3 REQUIRED NO_MODULE)
  message(STATUS "Eigen3 is found!")
endif()
# for eigen3 [before ^3.3]
if((NOT TARGET Eigen3::Eigen) AND (DEFINED EIGEN3_INCLUDE_DIR))
    add_library(AliasEigen3 INTERFACE)
    target_include_directories(AliasEigen3 INTERFACE ${EIGEN3_INCLUDE_DIR})
    add_library(Eigen3::Eigen ALIAS AliasEigen3)
endif()


#------------------ build source config ------------------

# include path
include_directories(include)

# sub directories
add_subdirectory(lib)

# libraries
add_library(${PROJECT_NAME} INTERFACE)
  target_link_libraries(${PROJECT_NAME} INTERFACE Eigen3::Eigen)
  target_link_libraries(${PROJECT_NAME} INTERFACE ${PROJECT_NAME}-reader)
  # if want to add libraries...
  # target_link_libraries(${PROJECT_NAME} INTERFACE ${PROJECT_NAME}-tool_name)

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
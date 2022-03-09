
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
  COMMAND file(REMOVE_RECURSE ${PROJECT_SOURCE_DIR}/temp)
  VERBATIM
  )
endif(CMAKE_COMPILER_IS_GNUCXX)
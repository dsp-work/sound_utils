if(MSVC)
  find_package(Eigen3 CONFIG)

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
      # Check if population has already been performed
      FetchContent_GetProperties(eigen3)
      if(NOT eigen3_POPULATED)
        # Fetch the content using previously declared details
        FetchContent_Populate(eigen3)

        # Bring the populated content into the build
        add_library(Eigen3::Eigen INTERFACE IMPORTED GLOBAL)
        target_include_directories(Eigen3::Eigen SYSTEM INTERFACE ${eigen3_SOURCE_DIR})
      endif()
    else()
      message(STATUS "Please install Eigen3 your self.")
    endif()
  endif()
    
else()

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

endif()
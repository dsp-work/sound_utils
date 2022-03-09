set(dsp_work_utils-with-test OFF CACHE BOOL "build flag of test for dsp_work_utils" FORCE)
find_package(dsp_work_utils NO_MODULE)
if (dsp_work_utils_FOUND)
  message(STATUS "DspWork::Utils is found!")
else() # 見つからない場合には自動インストール
  message(STATUS "DspWork::Utils is not found!")

  option(${PROJECT_NAME}-auto-install-dsp_work_utils "Enable auto installing of dsp_work_utils." ON)
  if(${PROJECT_NAME}-auto-install-dsp_work_utils)
    message(STATUS "Start auto installing dsp_work_utils...")
    message(STATUS "-- If you want not to install dsp_work_utils automatically, Configure with `-D${PROJECT_NAME}-auto-install-dsp_work_utils=OFF`.")
    include(FetchContent)
    FetchContent_Declare(
      dsp_work_utils
      GIT_REPOSITORY https://github.com/dsp-work/dsp_work_utils.git
      GIT_TAG 0.0.2
    )
    FetchContent_MakeAvailable(dsp_work_utils)
  else()
    message(STATUS "Please install dsp_work_utils your self.")
  endif()

  #find_package(dsp_work_utils REQUIRED NO_MODULE)
  #message(STATUS "dsp_work_utils is found!")
endif()
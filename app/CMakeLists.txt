project(android-base64)
cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_VERBOSE_MAKEFILE on)
set(EXECUTABLE_OUTPUT_PATH   "r:/${ANDROID_ABI}")

add_executable(base64
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/base64_main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/base64.cpp
    )
target_include_directories (base64 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

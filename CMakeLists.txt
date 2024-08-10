cmake_minimum_required(VERSION 3.16)
project(PERSONAL_PROJECT LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g3 -O0 -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -DNDEBUG -pthread")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

include_directories(include)
add_subdirectory(src)

add_subdirectory(googletest)
option(BP_BUILD_TESTS "Build tests" ON)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BP_BUILD_TESTS)
    include(GoogleTest)
    enable_testing()
    add_subdirectory(test)
endif()

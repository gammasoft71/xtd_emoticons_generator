cmake_minimum_required(VERSION 3.3)

# Solution
project(xtd_emoticons_generator)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
else ()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/${CMAKE_CURRENT_BINARY_DIR})
endif ()

add_subdirectory(xtd_emoticons_generator)

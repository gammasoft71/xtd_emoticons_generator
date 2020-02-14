cmake_minimum_required(VERSION 3.3)

# Project
project(xtd_emoticons_generator VERSION 1.0.0)
find_package(xtd REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${jsoncpp_INCLUDE_DIRS})

set(SOURCES
  src/xtd_emoticons_generator.cpp
)
source_group(src FILES ${SOURCES})
source_group(include FILES ${HEADERS})

# Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Application properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} xtd ${jsoncpp_LIBRARIES})

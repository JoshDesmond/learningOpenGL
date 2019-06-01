cmake_minimum_required(VERSION 3.14)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(OpenGL ${SOURCE_FILES})

include(FindPkgConfig)
find_package(libglfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})

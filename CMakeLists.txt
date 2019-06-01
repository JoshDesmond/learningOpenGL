cmake_minimum_required(VERSION 3.14)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp)

add_executable(OpenGL ${SOURCE_FILES})
target_link_libraries(OpenGL ${CMAKE_SOURCE_DIR}/include/glfw/lib-mingw-w64/libglfw3.a)

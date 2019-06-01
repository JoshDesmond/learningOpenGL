cmake_minimum_required(VERSION 3.14)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(OpenGL src/main.cpp)
target_link_libraries(OpenGL ${CMAKE_SOURCE_DIR}/lib/glfw/lib-mingw-w64/libglfw3.a)

set(FIND_GLFW_PATHS
        ${CMAKE_SOURCE_DIR}/include/GLFW)

message(STATUS "FIND_GLFW_PATHS = " ${FIND_GLFW_PATHS})

find_path(GLFW_INCLUDE_DIR
        NAMES glfw3.h glfw3native.h
        PATHS ${FIND_GLFW_PATHS}/include/GLFW/)

message(STATUS "GLFW_INCLUDE_DIR = " ${GLFW_INCLUDE_DIR})

find_library(GLFW_LIBRARY
        NAMES libglfw3
        PATHS ${FIND_GLFW_PATHS}/lib-mingw-w64/)

message(STATUS "GLFW_LIBRARY = " ${GLFW_LIBRARY})
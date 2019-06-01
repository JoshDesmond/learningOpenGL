set(FIND_GLFW_PATHS
        ${CMAKE_SOURCE_DIR}/include/GLFW)

find_path(GLFW_INCLUDE_DIR glfw3.h glfw3native.h
        PATH_SUFFIXES include/GLFW
        PATHS ${FIND_GLFW_PATHS})

find_library(GLFW_LIBRARY
        NAMES libglfw3
        PATH_SUFFIXES lib-mingw-w64
        PATHS ${FIND_GLFW_PATHS})
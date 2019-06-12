# Standard Stuff
cmake_minimum_required(VERSION 3.14)
project(OpenGL)
set(CMAKE_CXX_STANDARD 17)

# Set file location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Add executable for source files
set(SOURCE_FILES src/main.cpp src/Renderer.cpp src/Renderer.h src/VertexBuffer.cpp src/VertexBuffer.h src/IndexBuffer.cpp src/IndexBuffer.h src/VertexArray.cpp src/VertexArray.h src/VertexBufferLayout.h)
add_executable(OpenGL ${SOURCE_FILES})

# add cmake folder as modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# ================
# Handle Libraries
# ================

# GLFW
find_package(libglfw3 REQUIRED)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${GLFW_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})

# GLEW
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/include/glew-2.1.0/include")
list(APPEND CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/include/glew-2.1.0/lib")
find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)


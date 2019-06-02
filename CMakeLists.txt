# Standard Stuff
cmake_minimum_required(VERSION 3.14)
project(OpenGL)
set(CMAKE_CXX_STANDARD 17)

# Add executable for source files
set(SOURCE_FILES src/main.cpp)
add_executable(OpenGL ${SOURCE_FILES})

# add cmake folder as modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# ================
# Handle Libraries
# ================

# GLFW
find_package(libglfw3 REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${GLFW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY} ${OPENGL_LIBRARIES})

# find_package(GLEW REQUIRED)
#target_link_libraries(YourTarget GLEW::GLEW)
#Apparently you can just use the above line instead of adding the directories and libraries as below?


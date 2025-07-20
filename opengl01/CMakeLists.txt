cmake_minimum_required(VERSION 3.10)
# this makes CMake write build/compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(OpenGL01 LANGUAGES C CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Add include/ directory to header search path
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the executable target
add_executable(MyOpenGLApp
    src/main.cpp
    src/glad.c
)

# Link required libraries
target_link_libraries(MyOpenGLApp glfw GL dl pthread)


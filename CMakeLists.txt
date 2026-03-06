# Minimum version of CMake required to process this file.
# Ensures whoever builds your project has a modern enough CMake.
cmake_minimum_required(VERSION 3.20)

# Declares the project name, version, and that we're using C++.
# This sets useful variables like PROJECT_NAME behind the scenes.
project(Raycaster VERSION 1.0 LANGUAGES C CXX)

# Tell CMake we want C++17 features
set(CMAKE_CXX_STANDARD 17)

# If compiler does NOT support C++17, throw an error instead of silently falling
# back to older standard.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Look for OpenGL on the system and store it so we can link against it.
# REQUIRED means CMake will error out if OpenGL isn't found
find_package(OpenGL REQUIRED)

# Same but for GLFW - finds the library installed via dnf
find_package(glfw3 REQUIRED)

# Define the executable we want to build.
# PROJECT_NAME expands to "Raycaster" from the project() call above
# src/main.cpp is the source file to compile
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/gl.c    
)

# Tell the compiler to look in the include/ folder for header files.
# PRIVATE means only this target needs it, not anything that links to it
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link our executable against OpenGL and GLFW
# PRIVATE again means these are implementation details of our binary
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    OpenGL::GL # The OpenGL library found by find_package(OpenGL)
    glfw       # The GLFW library found by find_package(glfw3)
)
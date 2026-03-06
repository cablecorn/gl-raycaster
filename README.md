A Wolfenstein-style raycaster built in C++ using modern OpenGL (3.3 Core), 
GLFW, and GLAD 2.0. Built from scratch as a deep dive into GPU programming 
and real-time rendering.

The fundamentals of this project is from the tutorial given by https://learnopengl.com/Getting-started/OpenGL (donate if you can!)

## Building
```bash
sudo dnf install glfw-devel mesa-libGL-devel gcc-c++ cmake
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/Raycaster
```markdown

## Dev Log

### 03/06/2026:

 - Learned and reviewed the fundamentals of VBOs, VAOs, and shader coding (glsl)
 - Understanding the concepts of CPU <--> GPU communication

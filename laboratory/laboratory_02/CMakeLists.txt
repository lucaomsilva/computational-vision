# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and language
project(Laboratory02 CXX)

# Set the C++ standard to C++17 for modern features. This is good practice.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required OpenCV package.
# This command finds the headers and libraries for OpenCV.
find_package(OpenCV REQUIRED)

# Create an executable target for src/main.cpp.
add_executable(main src/main.cpp)

# Link the executable to the OpenCV libraries.
# This ensures your program can find the OpenCV functions it needs.
target_link_libraries(main PRIVATE ${OpenCV_LIBS})

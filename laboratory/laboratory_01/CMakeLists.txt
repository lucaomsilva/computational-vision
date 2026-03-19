# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and language
project(Laboratory01 CXX)

# Set the C++ standard to C++17 for modern features. This is good practice.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required OpenCV package.
# This command finds the headers and libraries for OpenCV.
find_package(OpenCV REQUIRED)

# --- Define your exercises here ---
# Add the path to each of your exercise source files to this list.
# For example, if you have exercise1.cpp and exercise2.cpp in your 'src' folder.
set(EXERCISE_SOURCES
    src/main.cpp # The original test file
    src/exercise_01.cpp
    src/exercise_02.cpp
    src/exercise_03.cpp
    src/exercise_04.cpp
    src/exercise_05.cpp
    src/exercise_06.cpp
    src/exercise_07.cpp
)

# This loop goes through each file in the list above and creates a build target for it.
foreach(SOURCE_FILE ${EXERCISE_SOURCES})
    # Get the filename without the path and extension (e.g., "src/exercise1.cpp" -> "exercise1")
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)

    # Create an executable target.
    # This tells CMake to create a program named ${TARGET_NAME} from the ${SOURCE_FILE}.
    add_executable(${TARGET_NAME} ${SOURCE_FILE})

    # Link the executable to the OpenCV libraries.
    # This ensures your program can find the OpenCV functions it needs.
    target_link_libraries(${TARGET_NAME} PRIVATE ${OpenCV_LIBS})
endforeach()

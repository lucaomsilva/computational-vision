# Laboratory 02: Thresholding and Filtering

This directory contains the exercises for the second laboratory session of the Computational Vision course. The main goal is to explore image thresholding, convolution, and various filtering techniques for smoothing and edge detection.

## Objective

This set of exercises builds upon the fundamentals from the previous lab. Each source file focuses on a specific task related to image filtering and analysis.

*   `main.cpp`: Implements the Hough Transform for circle detection in images of food plates.

## Prerequisites

Before you can build and run these exercises, you need to have the following software installed on your system:

1.  A C++ compiler (e.g., g++).
2.  `CMake` (version 3.10 or higher).
3.  The OpenCV library, including the development headers (`-devel` package).

For detailed installation instructions on Fedora, please refer to the guide in this repository:
`laboratory/laboratory_01/docs/instalacao_gpp_opencv_fedora.md`

Or use the `laboratory/laboratory_01/docs/instalacao_gpp_opencv_ubuntu` if you use Ubuntu distro.

## How to Build the Exercises

This project uses CMake to manage the build process. The `CMakeLists.txt` file is configured to create a executable for the code.

### 1. Prepare the Dataset

The exercises in this lab use a dataset of cell images located in `img/sel_data.zip`. Before building, you must unzip this file. You can do this easily with the provided Makefile target:

```bash
# Unzip the image files
make unzip
```

### 2. Compile the code

After unzip the images, you can compile the code easily with the provided command or Makefile target:

```bash
# Create a build directory
mkdir build

# Navigate into the build directory
cd build

# Run CMake to configure the project
cmake ..

# Or use
# Create the build directory and compile the project
make build
```

After a successful compilation, the `build/` directory will contain the following executables:

*   `main`

## How to Run the Exercises

The exercise that load an image expect to find the sample images at the path `img/sel_data/`. Because the executables are run from the `build` directory, you need to execute them from the project's root (`laboratory_02`) for the relative path to work correctly.

**Important:** Make sure you are in the `laboratory_02` directory before running the commands below. If you are inside `build/`, first go back with `cd ..`.

```bash
# Example of running main from the laboratory_02/ directory
./build/main
```

When you run an exercise that displays an image, a window will appear. Press *q* key to close it and terminate the program.

### Example Workflow

```bash
cd /path/to/computational-vision/laboratory/laboratory_02

make unzip

make build

./build/main
``` 

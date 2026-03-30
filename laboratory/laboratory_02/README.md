# Laboratory 02: Thresholding and Filtering

This directory contains the exercises for the second laboratory session of the Computational Vision course. The main goal is to explore image thresholding, convolution, and various filtering techniques for smoothing and edge detection.

## Objective

This set of exercises builds upon the fundamentals from the previous lab. Each source file in the `src/` directory focuses on a specific task related to image filtering and analysis.

*   `exercise_01.cpp`: Implements convolution to find a pattern (template) within a larger image, prints its location, and displays a 50x50 crop of the found region with padding if necessary.
*   `exercise_02.cpp`: Applies Gaussian, mean, median, and mode smoothing filters with different window sizes to a dataset of cell images to improve thresholding results for cell segmentation. Compares the effectiveness of each filter.
*   `exercise_03.cpp`: Uses first and second derivative filters (e.g., Sobel, Laplacian) to enhance the nuclei and contours of cells. It also estimates the predominant gradient direction in the images.

## Prerequisites

Before you can build and run these exercises, you need to have the following software installed on your system:

1.  A C++ compiler (e.g., g++).
2.  `CMake` (version 3.10 or higher).
3.  The OpenCV library, including the development headers (`-devel` package).

For detailed installation instructions on Fedora, please refer to the guide in this repository:
`docs/instalacao_gpp_opencv_fedora.md`

Or use the `docs/instalacao_gpp_opencv_ubuntu` if you use Ubuntu distro.

## How to Build the Exercises

This project uses CMake to manage the build process. The `CMakeLists.txt` file is configured to automatically find all exercise source files in the `src/` directory and create a separate executable for each one.

To compile all exercises, navigate to the `laboratory_02` directory and run the following commands:

```bash
# Create a build directory
mkdir build

# Navigate into the build directory
cd build

# Run CMake to configure the project
cmake ..

# Compile the project
make
```

After a successful compilation, the `build/` directory will contain the following executables:

*   `exercise_01`
*   `exercise_02`
*   `exercise_03`

## How to Run the Exercises

The exercises that load an image (all except `main`) expect to find the sample image at the path `img/imagem.jpg`. Because the executables are run from the `build` directory, you need to execute them from the project's root (`laboratory_02`) for the relative path to work correctly.

**Important:** Make sure you are in the `laboratory_02` directory before running the commands below. If you are inside `build/`, first go back with `cd ..`.

```bash
# Example of running exercise_02 from the laboratory_01/ directory
./build/exercise_02
```

When you run an exercise that displays an image, a window will appear. Press any key to close it and terminate the program. For `exercise_03`, you will need to enter the coordinates in the terminal first.

### Example Workflow

```bash
cd /path/to/computational-vision/laboratory/laboratory_02

mkdir build

./build/exercise_02
``` 

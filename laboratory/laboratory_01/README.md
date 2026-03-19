# Laboratory 01: Introduction to OpenCV

This directory contains the first set of exercises for the Computational Vision course. The main goal is to set up a C++/OpenCV development environment and practice fundamental image processing operations.

## Objective

The exercises are designed to provide a hands-on introduction to the OpenCV library. Each file focuses on a specific basic task:

*   `main.cpp`: A simple test program to verify that the OpenCV installation and compilation toolchain are working correctly. It creates and displays a solid green image.
*   `exercise_01.cpp`: Loads an image from a file, prints its properties (width, height, and number of channels) to the console, and displays it.
*   `exercise_02.cpp`: Loads a color image, converts it to grayscale, and displays both the original and the grayscale versions side-by-side in a single window.
*   `exercise_03.cpp`: Converts an image to grayscale and prompts the user to enter (x, y) coordinates to retrieve and print the pixel intensity at that specific point.
*   `exercise_04.cpp`: Loads an image, converts it to grayscale, computes its negative, and displays both the grayscale and negative images side-by-side.
*   `exercise_05.cpp`: Applies a binary threshold to a grayscale image, converting it to a black-and-white image.
*   `exercise_06.cpp`: Applies a quantization on a grayscale image (128, 64, 16 and 4), converting it to a black-and-white image.
*   `exercise_07.cpp`: Demonstrates resolution loss by downsampling and then upsampling an image.
*   `exercise_08.cpp`: Shows the combined effect of resolution reduction and color quantization on an image.

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

To compile all exercises, execute this command from the `laboratory_01` directory:

```bash
mkdir build
```

After a successful compilation, the `build/` directory will contain the following executables:

*   `main`
*   `exercise_01`
*   `exercise_02`
*   `exercise_03`
*   `exercise_04`
*   `exercise_05`
*   `exercise_06`
*   `exercise_07`
*   `exercise_08`

## How to Run the Exercises

The exercises that load an image (all except `main`) expect to find the sample image at the path `img/imagem.jpg`. Because the executables are run from the `build` directory, you need to execute them from the project's root (`laboratory_01`) for the relative path to work correctly.

**Important:** Make sure you are in the `laboratory_01` directory before running the commands below. If you are inside `build/`, first go back with `cd ..`.

```bash
# Example of running exercise_01 from the laboratory_01/ directory
./build/exercise_01
```

When you run an exercise that displays an image, a window will appear. Press any key to close it and terminate the program. For `exercise_03`, you will need to enter the coordinates in the terminal first.

### Example Workflow

```bash
cd /path/to/computational-vision/laboratory/laboratory_01

mkdir build

./build/exercise_02
``` 

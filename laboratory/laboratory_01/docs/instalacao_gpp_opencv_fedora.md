# Tutorial: Installing g++ and OpenCV on Fedora Linux

> **Objective:** Install the C++ compiler (g++), basic compilation tools, and the OpenCV library on Fedora, then verify the installation with a minimal test program.

## Recommended Method

This tutorial uses the `dnf` package manager from Fedora's official repositories. This is the simplest and most suitable option for an introductory course. OpenCV can also be compiled from source code when specific features or a custom version are needed, but this is not necessary to get started with the course.

---

### 1. Prerequisites

Before you begin, it is highly recommended to update your system to ensure all packages are current. You will need `sudo` permissions to execute the installation commands.

Open a terminal and run:
```bash
sudo dnf update -y
```
> **Tip:** If you have just installed Fedora, rebooting after the first major update can help prevent issues with newly loaded libraries and kernel modules.

### 2. Installing the g++ Compiler and Basic Tools

First, install the C++ compiler and a complete set of development tools. On Fedora, the `Development Tools` group package provides essential utilities like the compiler (g++), linker, and `make`, similar to `build-essential` on Debian/Ubuntu systems.

```bash
sudo dnf groupinstall "Development Tools"
```

It is also very useful to install `CMake` and `pkg-config`. These tools help manage build processes and automatically locate the necessary library files for compilation, especially for projects using OpenCV.

```bash
sudo dnf install cmake pkg-config
```

#### Verifying g++

After the installation, verify that the compiler is available and ready to use:

```bash
g++ --version
```

If a version number is displayed (e.g., `g++ (GCC) 13.2.1...`), the compiler has been successfully installed on your system.

### 3. Installing OpenCV on Fedora

For a learning environment and initial C++ exercises, the easiest method is to install the pre-compiled packages available directly from Fedora's repositories. You will need both the main library (`opencv`) and the development files (`opencv-devel`), which contain the headers required for compilation.

```bash
sudo dnf install opencv opencv-devel
```

#### Verifying OpenCV

Use `pkg-config` to confirm that the OpenCV library is visible to the compiler.

```bash
pkg-config --modversion opencv4
```

On most modern Fedora systems, the package name for `pkg-config` is `opencv4`. If a version number appears (e.g., `4.9.0`), the installation is recognized and ready for use.

> **If you get an error from `pkg-config`:** This might happen on different system versions. Ensure the `pkg-config` package is installed and try to find the correct OpenCV package name with `dnf search opencv` or `pkg-config --list-all | grep opencv`. However, `opencv4` is the standard on current Fedora releases.

### 4. Testing with a Minimal C++ Program

Create a file named `main.cpp` with the following content. This program creates a simple green image and displays it in a window, confirming that the graphics and core modules of OpenCV are working.

```cpp
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Create a 300x400 image, 3-channel (color), with a green background
    cv::Mat img(300, 400, CV_8UC3, cv::Scalar(0, 255, 0));

    // Check if the image was created
    if (img.empty()) {
        std::cout << "Error: Could not create the image." << std::endl;
        return -1;
    }

    // Display the image in a window
    cv::imshow("OpenCV Test", img);

    // Wait for a key press
    cv::waitKey(0);

    std::cout << "OpenCV is working correctly." << std::endl;
    return 0;
}
```

#### Direct Compilation from the Terminal

Compile the program using g++. The `pkg-config` tool is used here to automatically supply the compiler and linker with the correct flags for OpenCV.

```bash
g++ main.cpp -o teste_opencv $(pkg-config --cflags --libs opencv4)
```

> **A note on the command:** The `$(...)` syntax executes the `pkg-config` command and substitutes its output directly into the `g++` command. This is the modern and more readable alternative to using backticks (`` `...` ``).

If the compilation finishes without errors, run the program:

```bash
./teste_opencv
```

If a green window titled "OpenCV Test" appears, your basic C++ and OpenCV installation is functioning correctly.

### 5. Compiling with CMake

For any project larger than a single file, the recommended method for building with OpenCV is to use `CMake`.

1.  Create a file named `CMakeLists.txt` in the same directory as `main.cpp`:

    ```cmake
    cmake_minimum_required(VERSION 3.10)
    project(TesteOpenCV)

    find_package(OpenCV REQUIRED)

    add_executable(teste_opencv main.cpp)
    target_link_libraries(teste_opencv ${OpenCV_LIBS})
    ```

2.  Then, compile the project with these commands:

    ```bash
    # Create a separate directory for build files
    mkdir build
    cd build

    # Run CMake to configure the project and generate Makefiles
    cmake ..

    # Run make to compile the code
    make

    # Run the executable
    ./teste_opencv
    ```

### 6. Common Problems and How to Solve Them

*   **Error: `fatal error: opencv2/opencv.hpp: No such file or directory`**
    This error means the compiler cannot find the OpenCV header files. It usually indicates that the development package is not installed or that the compilation command is missing the correct flags.
    **Solution:** Install the development files with `sudo dnf install opencv-devel` and ensure your `g++` command includes `$(pkg-config --cflags --libs opencv4)`.

*   **Error: Cannot open a graphical window (e.g., `Gtk-WARNING **: cannot open display:`)**
    If you are in an environment without a graphical interface (like a minimal container, a server, or an SSH session without X11 forwarding), `imshow` will fail because it cannot create a window.
    **Solution:** Test your code on a local desktop session or configure X11 forwarding for your SSH connection.

*   **Error: `bash: pkg-config: command not found`**
    The `pkg-config` utility is not installed.
    **Solution:** `sudo dnf install pkg-config`

*   **Error: `bash: g++: command not found`**
    The g++ compiler is not installed or not in your system's PATH.
    **Solution:** `sudo dnf groupinstall "Development Tools"`

### 7. Summary of Main Commands

```bash
# Update system
sudo dnf update -y

# Install compiler and build tools
sudo dnf groupinstall "Development Tools"
sudo dnf install cmake pkg-config

# Install OpenCV library and development files
sudo dnf install opencv opencv-devel

# Verify installations
g++ --version
pkg-config --modversion opencv4

# Compile and run test program
g++ main.cpp -o teste_opencv $(pkg-config --cflags --libs opencv4)
./teste_opencv
```

### 8. References

The instructions in this tutorial are based on official documentation from Fedora and OpenCV.

*   OpenCV Documentation - Installation in Linux
*   OpenCV Documentation - Using OpenCV with gcc and CMake
*   Fedora Developer Portal
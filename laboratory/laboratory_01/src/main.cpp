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

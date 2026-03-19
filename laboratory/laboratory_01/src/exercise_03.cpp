#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    string image_path = "img/imagem.jpg";

    Mat image = imread(image_path);

    if (image.empty()) {
        cout << "Error: Could not read the image at path: " << image_path << endl;
        return 1;
    }

    cout << "Image loaded successfully." << endl;

    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    ~Mat(image);

    int x, y;

    cout << "Enter the x coordinate: ";
    cin >> x;

    cout << "Enter the y coordinate: ";
    cin >> y;

    if (y >= 0 && y < gray_image.rows && x >= 0 && x < gray_image.cols) {
      // The .at<uchar> method is used for 8-bit single-channel images
      // Note: OpenCV uses (y, x) indexing for the .at function
      uchar pixel_intensity = gray_image.at<uchar>(y, x);
      cout << "The grayscale intensity at (" << x << ", " << y << ") is: " << (int)pixel_intensity << endl;
    } else {
      cout << "Error: The coordinates (" << x << ", " << y << ") are outside the image boundaries." << endl;
    }

    ~Mat(gray_image);

    return 0;
}

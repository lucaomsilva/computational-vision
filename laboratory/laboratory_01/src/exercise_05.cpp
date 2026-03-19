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

    const double thresh = 128;
    const double maxval = 255;

    Mat binary_image;
    (void)threshold(gray_image, binary_image, thresh, maxval, THRESH_BINARY);

    imshow("Binary", binary_image);

    while (waitKey(1) != 'q');

    destroyAllWindows();

    ~Mat(binary_image);

    return 0;
}

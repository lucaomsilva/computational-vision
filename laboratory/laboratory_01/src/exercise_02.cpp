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

    // To display images side-by-side in one window, they must have the same number of channels.
    // We convert the 1-channel grayscale image back to a 3-channel BGR image.
    Mat gray_bgr_image;
    cvtColor(gray_image, gray_bgr_image, COLOR_GRAY2BGR);

    ~Mat(gray_image);

    // Horizontally concatenate the original and the BGR-converted grayscale image.
    Mat combined_image;
    hconcat(image, gray_bgr_image, combined_image);

    ~Mat(image);
    ~Mat(gray_bgr_image);

    imshow("Original vs. Grayscale", combined_image);

    while (waitKey(1) != 'q');

    destroyAllWindows();

    ~Mat(combined_image);

    return 0;
}

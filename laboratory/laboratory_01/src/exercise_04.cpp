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

    const uchar maxval = 255;

    Mat negative_image;
    negative_image = maxval - gray_image;

    Mat combined_image;
    hconcat(gray_image, negative_image, combined_image);

    imshow("Grayscale vs Negative", combined_image);

    ~Mat(gray_image);
    ~Mat(negative_image);

    while (waitKey(1) != 'q');

    destroyAllWindows();

    ~Mat(combined_image);

    return 0;
}

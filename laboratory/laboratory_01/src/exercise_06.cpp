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

    Mat gray_image_128 = gray_image.clone();
    gray_image_128 &= 0b10000000;

    Mat gray_image_64 = gray_image.clone();
    gray_image_64 &= 0b01000000;

    Mat combined_image1;
    hconcat(gray_image_128, gray_image_64, combined_image1);

    ~Mat(gray_image_128);
    ~Mat(gray_image_64);

    Mat gray_image_16 = gray_image.clone();
    gray_image_16 &= 0b00010000;

    Mat gray_image_4 = gray_image.clone();
    gray_image_4 &= 0b00000100;

    ~Mat(gray_image);

    Mat combined_image2;
    hconcat(gray_image_16, gray_image_4, combined_image2);

    ~Mat(gray_image_16);
    ~Mat(gray_image_4);

    Mat combined_image;
    vconcat(combined_image1, combined_image2, combined_image);

    ~Mat(combined_image1);
    ~Mat(combined_image2);

    imshow("Gray Scales", combined_image);

    while (waitKey(1) != 'q');

    destroyAllWindows();

    ~Mat(combined_image);

    return 0;
}

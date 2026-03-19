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

    const double scale_down = 0.5;

    Mat reduce_image;
    resize(image, reduce_image, Size(), scale_down, scale_down, INTER_LINEAR);

    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    gray_image &= 0b00100000;

    Mat reduce_gray_image;
    cvtColor(reduce_image, reduce_gray_image, COLOR_BGR2GRAY);
    reduce_gray_image &= 0b00100000;

    imshow("reduce image", reduce_image);
    imshow("gray image", gray_image);
    imshow("reduce gray image", reduce_gray_image);

    cout << "-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= " << endl;
    cout << "Reducing the image resolution makes the pixels more tightly packed, resulting in a sharper image."
      << "\nSimilarly, in the case of a grayscale image, the visible grain becomes less noticeable." << endl;
    cout << "-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= " << endl;

    while (waitKey(1) != 'q');

    destroyAllWindows();

    ~Mat(image);
    ~Mat(reduce_image);
    ~Mat(gray_image);
    ~Mat(reduce_gray_image);

    return 0;
}

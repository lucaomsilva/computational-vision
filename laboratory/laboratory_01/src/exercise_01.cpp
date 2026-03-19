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

    int width = image.cols;
    int height = image.rows;
    int channels = image.channels();

    cout << "Dimensions: " << width << " x " << height << " pixels." << endl;
    cout << "Channels: " << channels << "." << endl;

    imshow("Image Display", image);

    while (waitKey(1) != 'q');

    destroyAllWindows();

    ~Mat(image);

    return 0;
}

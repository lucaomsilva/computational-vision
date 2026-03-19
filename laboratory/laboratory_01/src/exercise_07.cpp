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
    const double scale_up = 2;

    Mat reduce_image;
    resize(image, reduce_image, Size(), scale_down, scale_down, INTER_LINEAR);

    Mat extend_image;
    resize(reduce_image, extend_image, Size(), scale_up, scale_up, INTER_LINEAR);

    imshow("image", image);
    imshow("reduce", reduce_image);
    imshow("extend", extend_image);

    while (waitKey(1) != 'q');

    destroyAllWindows();

    ~Mat(image);
    ~Mat(reduce_image);
    ~Mat(extend_image);

    return 0;
}

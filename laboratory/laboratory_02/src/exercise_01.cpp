#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#define PADDING 25

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

    Rect template_roi(100, 100, 80, 80);
    Mat template_image = image(template_roi).clone();

    Mat gray_image, gray_template;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    cvtColor(template_image, gray_template, COLOR_BGR2GRAY);

    Point best_match_loc;
    double minimun_sum = -1;

    for (int y=0; y<=gray_image.rows-gray_template.rows; y++) {
        for (int x=0; x<=gray_image.cols-gray_template.cols; x++) {
            double current_sum = 0.0;

            for (int ty=0; ty<gray_template.rows; ty++) {
                for (int tx=0; tx<gray_template.cols; tx++) {
                    uchar image_pixel = gray_image.at<uchar>(y + ty, x + tx);
                    uchar template_pixel = gray_template.at<uchar>(ty, tx);

                    double diff = image_pixel - template_pixel;
                    current_sum += diff * diff;
                }
            }

            if (minimun_sum == -1 || current_sum < minimun_sum) {
                minimun_sum = current_sum;
                best_match_loc = Point(x, y);
            }
        }
    }
    Point match_loc = best_match_loc;

    cout << "Most similar position (top-left corner) found at: " << match_loc << endl;

    rectangle(image, match_loc, Point(match_loc.x + template_image.cols, match_loc.y + template_image.rows), Scalar(0, 255, 0), 2);

    Point match_center(match_loc.x + template_image.cols / 2, match_loc.y + template_image.rows / 2);

    Mat padded_image;
    copyMakeBorder(image, padded_image, PADDING, PADDING, PADDING, PADDING, BORDER_CONSTANT, Scalar(0, 0, 0));

    Point padded_center(match_center.x + PADDING, match_center.y + PADDING);
    Rect roi(padded_center.x - 25, padded_center.y - 25, 50, 50);
    Mat centered_region = padded_image(roi);

    imshow("Template", template_image);
    imshow("Found Match", image);
    imshow("50x50 Centered Region", centered_region);

    while (waitKey(0) != 'q');

    destroyAllWindows();

    return 0;
}

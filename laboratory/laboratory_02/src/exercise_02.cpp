#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#define DIMENSION 256

using namespace std;
using namespace cv;

Mat create_gaussian_kernel(int kernel_size, double sigma) {
    Mat kernel = Mat::zeros(kernel_size, kernel_size, CV_64F);
    int m = kernel_size / 2;
    double sum = 0.0;
    
    for (int i = -m; i <= m; i++) {
        for (int j = -m; j <= m; j++) {
            double val = exp(-(i * i + j * j) / (2 * sigma * sigma)) / (2 * CV_PI * sigma * sigma);
            kernel.at<double>(i + m, j + m) = val;
            sum += val;
        }
    }

    kernel /= sum;
    return kernel;
}

Mat apply_filter(const Mat& src, const Mat& kernel) {
    Mat dst = Mat::zeros(src.size(), src.type());
    int m = kernel.rows / 2;
    
    for (int i = m; i < src.rows - m; i++) {
        for (int j = m; j < src.cols - m; j++) {
            double sum = 0.0;
            for (int ki = -m; ki <= m; ki++) {
                for (int kj = -m; kj <= m; kj++) {
                    sum += src.at<uchar>(i + ki, j + kj) * kernel.at<double>(ki + m, kj + m);
                }
            }
            dst.at<uchar>(i, j) = saturate_cast<uchar>(sum);
        }
    }
    return dst;
}

Mat apply_mode_filter(const Mat& src, int kernel_size) {
    Mat dst = src.clone();
    int radius = kernel_size / 2;

    for (int y = radius; y < src.rows - radius; y++) {
        for (int x = radius; x < src.cols - radius; x++) {
            
            int histogram[256] = {0};
            
            for (int ky = -radius; ky <= radius; ky++) {
                for (int kx = -radius; kx <= radius; kx++) {
                    uchar pixel = src.at<uchar>(y + ky, x + kx);
                    histogram[pixel]++;
                }
            }
            
            int mode = 0;
            int max_count = 0;
            for (int i = 0; i < 256; i++) {
                if (histogram[i] > max_count) {
                    max_count = histogram[i];
                    mode = i;
                }
            }
            
            dst.at<uchar>(y, x) = (uchar)mode;
        }
    }
    return dst;
}

int main() {
    string image_path = "img/45701.jpg";

    Mat image = imread(image_path);

    if (image.empty()) {
        cout << "Error: Could not read the image at path: " << image_path << endl;
        return 1;
    }

    cout << "Image loaded successfully." << endl;

    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    resize(gray_image, gray_image, Size(DIMENSION, DIMENSION));

    imshow("Original Image", gray_image);

    int kernel_size = 9;
    double sigma = 3.0;
    
    Mat kernel = create_gaussian_kernel(kernel_size, sigma);
    Mat blurred = apply_filter(gray_image, kernel);

    Mat mean_kernel = Mat::ones(kernel_size, kernel_size, CV_64F) / (kernel_size * kernel_size);
    Mat mean_blurred = apply_filter(gray_image, mean_kernel);

    Mat median_blurred;
    medianBlur(gray_image, median_blurred, kernel_size);

    Mat mode_blurred = apply_mode_filter(gray_image, kernel_size);

    imshow("Blurred Image", blurred);
    imshow("Mean Blurred Image", mean_blurred);
    imshow("Median Blurred Image", median_blurred);
    imshow("Modal Blurred Image", mode_blurred);

    while (waitKey(0) != 'q');

    destroyAllWindows();

    return 0;
}

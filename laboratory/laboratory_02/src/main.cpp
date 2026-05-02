#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

struct Filter {
  string name;
  Mat img;
};

struct Circle {
  Point center;
  int radius;
};

Mat import_image(string image_path)
{
  Mat image = imread(image_path);

  if (image.empty()) {
    cout << "Error: Could not read the image at path: " << image_path << endl;
    return Mat();
  }

  return image;
}

uint8_t save_process_image(Mat image, string process_image_path)
{
  if (imwrite(process_image_path, image)) {
    return 1;
  }

  return 0;
}

// TODO: Create my hough transform function
void hough_transform(Mat image, vector<Circle> &best_circle, int radius_min, int radius_max)
{
  Mat gray;
  if (image.channels() == 3) {
    cvtColor(image, gray, COLOR_BGR2GRAY);
  } else {
    gray = image;
  }

  vector<Vec3f> circles;
  HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                gray.rows / 8,
                100, 30,
                radius_min, radius_max);

  best_circle.clear();
  for (size_t i = 0; i < circles.size(); i++) {
    Circle c;
    c.center = Point(cvRound(circles[i][0]), cvRound(circles[i][1]));
    c.radius = cvRound(circles[i][2]);
    best_circle.push_back(c);
  }
}

Mat draw_circle(Mat image, vector<Circle> best_circle, const int limit)
{
  Mat result = image.clone();
  for (int i = 0; i < min((int)best_circle.size(), limit); i++) {
    circle(result, best_circle[i].center, best_circle[i].radius, Scalar(0, 255, 0), 3, LINE_AA);
    circle(result, best_circle[i].center, 2, Scalar(0, 0, 255), 3, LINE_AA);
  }
  return result;
}

int main()
{
  string image_dir_path = "img/sel_data/";
  string output_dir_path = "img/output/";

  int images_lens = 1;

  for (int image_number = 0; image_number < images_lens; image_number++) {
    string image_path = image_dir_path + to_string(image_number) + ".jpg";
    Mat image = import_image(image_path);

    if (image.empty()) continue;

    vector<Filter> processed_images;

    // 1. Original (Grayscale)
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    processed_images.push_back({"gray", gray});

    // 2. Gaussian Blur
    Mat gaussian;
    GaussianBlur(gray, gaussian, Size(9, 9), 2, 2);
    processed_images.push_back({"gaussian", gaussian});

    // 3. Median Blur
    Mat median;
    medianBlur(gray, median, 5);
    processed_images.push_back({"median", median});

    for (auto& filter : processed_images) {
      int min_radius = 100;
      int max_radius = 250;
      int interval = 10;
      for (int radius_start = min_radius; radius_start <= max_radius; radius_start += interval) {
        for (int radius_end = radius_start + interval; radius_end <= max_radius; radius_end += interval) {
          vector<Circle> best_circle_hough;
          hough_transform(filter.img, best_circle_hough, radius_start, radius_end);

          Mat image_circle = draw_circle(image, best_circle_hough, (int) best_circle_hough.size());

          string process_image_path = output_dir_path + filter.name + "/" + to_string(image_number) + "_" + to_string(radius_start) + "_" + to_string(radius_end) + ".jpg";

          if (save_process_image(image_circle, process_image_path)) {
            cout << "Saved: " << process_image_path << endl;
          }
        }
      }
    }
  }

  return 0;
}

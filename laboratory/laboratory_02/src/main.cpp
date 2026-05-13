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
void hough_transform(Mat image, vector<Circle> &best_circle, int radius_min, int radius_max, const std::vector<double>& sinTable, const std::vector<double>& cosTable)
{
  Mat gray;
  if (image.channels() == 3) {
    cvtColor(image, gray, COLOR_BGR2GRAY);
  } else {
    gray = image;
  }

  // 1. Edge Detection (Canny)
  Mat edges;
  Canny(gray, edges, 50, 100);

  int width = edges.cols;
  int height = edges.rows;
  int num_radii = radius_max - radius_min + 1;

  if (num_radii <= 0) return;

  std::vector<std::vector<std::pair<int, int>>> circleOffsets(num_radii);
  for (int r = radius_min; r <= radius_max; r++) {
    int r_idx = r - radius_min;
    // Use a temporary array to avoid duplicate voting for the same pixel
    // To keep it simple and efficient, we can just use a 2D boolean array or std::set
    // We will use a fast array approach to filter unique offsets
    std::vector<std::pair<int, int>> unique_offsets;
    std::vector<bool> seen((2 * r + 1) * (2 * r + 1), false);
    int offset_center = r;
    
    for (int theta = 0; theta < 360; theta++) {
      int da = cvRound(r * cosTable[theta]);
      int db = cvRound(r * sinTable[theta]);
      int seen_idx = (da + offset_center) + (db + offset_center) * (2 * r + 1);
      if (!seen[seen_idx]) {
        seen[seen_idx] = true;
        unique_offsets.push_back({da, db});
      }
    }
    circleOffsets[r_idx] = unique_offsets;
  }

  // 3. 3D Accumulator (Linearized)
  int slice_size = width * height;
  std::vector<int> accumulator(slice_size * num_radii, 0);

  // 4. Voting Process
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (edges.at<uchar>(y, x) > 0) { // Edge pixel
        for (int r = radius_min; r <= radius_max; r++) {
          int r_idx = r - radius_min;
          int r_offset = r_idx * slice_size;
          for (const auto& offset : circleOffsets[r_idx]) {
            int a = x - offset.first;
            int b = y - offset.second;
            if (a >= 0 && a < width && b >= 0 && b < height) {
              accumulator[a + (b * width) + r_offset]++;
            }
          }
        }
      }
    }
  }

  // 5. Circle Detection (Local Maxima)
  int threshold = 30; 
  std::vector<std::pair<int, Circle>> candidates;

  for (int r = radius_min; r <= radius_max; r++) {
    int r_idx = r - radius_min;
    for (int b = 0; b < height; b++) {
      for (int a = 0; a < width; a++) {
        int idx = a + (b * width) + (r_idx * slice_size);
        int votes = accumulator[idx];
        if (votes >= threshold) {
          bool is_max = true;
          // Check 3x3x3 neighborhood
          for (int dr = -1; dr <= 1; dr++) {
            for (int db = -1; db <= 1; db++) {
              for (int da = -1; da <= 1; da++) {
                if (dr == 0 && db == 0 && da == 0) continue;
                int nr = r_idx + dr, nb = b + db, na = a + da;
                if (nr >= 0 && nr < num_radii && nb >= 0 && nb < height && na >= 0 && na < width) {
                  int n_idx = na + (nb * width) + (nr * slice_size);
                  if (accumulator[n_idx] > votes) {
                    is_max = false;
                    goto max_check_end;
                  }
                }
              }
            }
          }
          max_check_end:
          if (is_max) {
            Circle c;
            c.center = Point(a, b);
            c.radius = r;
            candidates.push_back({votes, c});
          }
        }
      }
    }
  }

  // Sort candidates by votes in descending order
  std::sort(candidates.begin(), candidates.end(), [](const std::pair<int, Circle>& a, const std::pair<int, Circle>& b) {
    return a.first > b.first;
  });

  // Filter overlapping circles (min distance)
  best_circle.clear();
  double min_dist = height / 8.0; 
  for (const auto& cand : candidates) {
    bool keep = true;
    for (const auto& existing : best_circle) {
      double dist = norm(cand.second.center - existing.center);
      if (dist < min_dist) {
        keep = false;
        break;
      }
    }
    if (keep) {
      best_circle.push_back(cand.second);
    }
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

  // Pre-calculate Sine and Cosine
  std::vector<double> sinTable(360), cosTable(360);
  for (int theta = 0; theta < 360; theta++) {
    double radian = theta * (CV_PI / 180.0);
    sinTable[theta] = sin(radian);
    cosTable[theta] = cos(radian);
  }

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
      int min_radius = 190;
      int max_radius = 220;
      int interval = 10;
      for (int radius_start = min_radius; radius_start <= max_radius; radius_start += interval) {
        for (int radius_end = radius_start + interval; radius_end <= max_radius; radius_end += interval) {
          vector<Circle> best_circle_hough;
          hough_transform(filter.img, best_circle_hough, radius_start, radius_end, sinTable, cosTable);

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

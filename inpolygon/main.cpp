#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME "CVUI"

bool inPolygon(std::vector<cv::Point> polygon, cv::Point target) {
  int closs_cnt = 0;

  for (int i = 0; i < polygon.size(); i++) {
    cv::Point pt1 = polygon[i];
    cv::Point pt2 = polygon[(i + 1) % polygon.size()];

    cv::Point vec1 = pt1 - target;
    cv::Point vec2 = pt2 - target;
    float ext = vec1.x * vec2.y - vec1.y * vec2.x;

    if ((vec1.y >= 0) && (vec2.y < 0) && (ext > 0)) {
      closs_cnt++;
    } else if ((vec1.y < 0) && (vec2.y >= 0) && (ext < 0)) {
      closs_cnt++;
    }
  }

  return (closs_cnt % 2) == 1;
}

int main(int argc, char* argv[]) {
  cv::Mat frame = cv::Mat(500, 500, CV_8UC3);
  int count = 0;

  cv::namedWindow(WINDOW_NAME);
  cvui::init(WINDOW_NAME);

  std::vector<cv::Point> pts;

  auto target = cv::Point(0, 0);
  auto color = cv::Scalar(0, 0, 0);

  while (true) {
    frame = cv::Scalar(48, 52, 49);

    cvui::text(frame, 30,0, "LEFTCLICK: move target, MIDDLE_CLICK: add point to polygon");

    if (cvui::mouse(cvui::MIDDLE_BUTTON, cvui::CLICK)) {
      cv::Point cursor = cvui::mouse();
      pts.push_back(cursor);
    } else if (cvui::mouse(cvui::LEFT_BUTTON, cvui::CLICK)) {
      target = cvui::mouse();
    }

    cv::circle(frame, target, 10, cv::Scalar(0,200,0), -1, CV_8U);

    int N = pts.size();

    if (inPolygon(pts, target)) {
      color = cv::Scalar(200, 0, 0);
    } else {
      color = cv::Scalar(0, 0, 200);
    }
    cv::polylines(frame, pts, true, color, 10, CV_8U);

    cvui::update();
    cv::imshow(WINDOW_NAME, frame);

    if (cv::waitKey(20) == 27) {
      break;
    }
  }
  return 0;
}

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define CVUI_IMPLEMENTATION
#include "cvui.h"

#define WINDOW_NAME "CVUI"

int main(int argc, char* argv[]) {
  cv::Mat frame = cv::Mat(200, 500, CV_8UC3);
  int count = 0;

  cv::namedWindow(WINDOW_NAME);
  cvui::init(WINDOW_NAME);

      while (true) {
    frame = cv::Scalar(48, 52, 49);
    if (cvui::button(frame, 110, 80, "hello,world")) {
      count++;
    }

    cvui::printf(frame, 250, 90, 0.3, 0xff0000, "Button Click: %d", count);
    cvui::update();

    cv::imshow(WINDOW_NAME,frame);

    if(cv::waitKey(20)==27){
      break;
    }
  }
  return 0;
}

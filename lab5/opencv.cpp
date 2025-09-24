#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        return -1;
    }

    cv::Mat frame;
    while (true) {
        capture >> frame;
        if (frame.empty()) break;

        cv::imshow("test", frame);

        char c = (char)cv::waitKey(33);
        if (c == 27) break; // ESC для выхода
    }

    capture.release();
    cv::destroyAllWindows();
    return 0;
}
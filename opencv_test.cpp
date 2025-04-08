#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat image = cv::imread("Baby.jpg");

    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }

    cv::imshow("Display window", image);
    cv::waitKey(0); // Wait for a keystroke in the window

    return 0;
}
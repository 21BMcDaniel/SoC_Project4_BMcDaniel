#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: ./edge_detect <image_path>" << std::endl;
        return -1;
    }

    std::string imagePath = argv[1];

    // Read the image in grayscale
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }

    // Apply Canny edge detection
    cv::Mat edges;
    cv::Canny(image, edges, 100, 200);

    // Save the result to file
    bool saved = cv::imwrite("outImage_McDaniel.jpg", edges);
    if (saved) {
        std::cout << "Edge image saved as outImage_McDaniel.jpg" << std::endl;
    } else {
        std::cerr << "Failed to save outImage_McDaniel.jpg" << std::endl;
    }

    // Display the result
    cv::imshow("Original Image", image);
    cv::imshow("Edge Detection", edges);

    std::cout << "Press any key in the image window to exit..." << std::endl;
    cv::waitKey(0); // Wait for a key press

    return 0;
}
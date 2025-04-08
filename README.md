# SoC_Project4_BMcDaniel
Project 4 for systemC and Opencv implementation of Image analysis. This project implements Transaction Level Modeling for the last task to produce a line detection algorithm for a road image.

## **Explanation of Files**
- Task One
  - Test.cpp file tests the systemC library whil the OpenCV.cpp file tests the OpenCV library. This confirms the proper environement set up for systemC and OpenCV.
- Task Two
  - edge_McDaniel.cpp provides the code that finds the edges of the provided test.jpg image (coins).
  - output is displayed in the file titles "outImage_McDaniel.jpg"
-Task Three
  - Memory.cpp, Processor1, Processor2, and Top.cpp are the files that complete task 3 to which an image is stored in processor1, loaded to memory, and then processor2 reads the memory file and completes the required algorithms and functions to complete the lines detection
  - the output file is stored in the file titled "final_output.jpg"

## **Results**

The final result showed successfully detected road lines in the processed image, with clear edges and well-defined lines. The image processing pipeline was able to effectively detect edges in the full image and focus line detection on the region where road lines typically appear.

## **Screenshots**

- **Original Image**:
  - Screenshot showing the input image before processing.
  
- **Edge Detection**:
  - Screenshot displaying the result of edge detection on the full image.

- **Detected Road Lines**:
  - Screenshot displaying the final result with road lines drawn in red.

## **Conclusion**

This project successfully demonstrated how to apply image processing techniques such as edge detection and line detection to detect road lines. By applying both full-image processing and region-specific (ROI) processing, the system was able to focus on the most relevant features. Despite some challenges, such as tuning the parameters for edge and line detection, the final result was a robust solution for detecting road lines in images.

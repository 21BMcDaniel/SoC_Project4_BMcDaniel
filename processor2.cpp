#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <opencv2/opencv.hpp>

using namespace sc_core;
using namespace cv;

struct Processor2 : sc_module {
    tlm_utils::simple_initiator_socket<Processor2> socket;

    SC_CTOR(Processor2) {
        SC_THREAD(process);
    }

    void process() {
        wait(100, SC_NS); // Ensure Processor1 completes first
    
        // 1. Receive data
        int meta_size = 3*sizeof(int);
        std::vector<unsigned char> buffer(meta_size + 1920*1080); // Max HD buffer
    
        tlm::tlm_generic_payload trans;
        sc_time delay = SC_ZERO_TIME;
        trans.set_command(tlm::TLM_READ_COMMAND);
        trans.set_address(0);
        trans.set_data_ptr(buffer.data());
        trans.set_data_length(buffer.size());
        socket->b_transport(trans, delay);
    
        // 2. Reconstruct image
        int width, height, type;
        std::memcpy(&width, buffer.data(), sizeof(int));
        std::memcpy(&height, buffer.data() + sizeof(int), sizeof(int));
        std::memcpy(&type, buffer.data() + 2*sizeof(int), sizeof(int));
    
        size_t expected_size = meta_size + width * height * CV_ELEM_SIZE(type);
        if (buffer.size() < expected_size) {
            SC_REPORT_ERROR("Memory Error", "Image data incomplete");
            return;
        }
    
        Mat received(height, width, type, buffer.data() + meta_size);
        Mat image = received.clone(); // Make a deep copy
    
        // === ROI-Based Edge + Line Detection ===
        // ==== EDGE DETECTION ====
        Mat edges_full;
        Canny(image, edges_full, 50, 150); // Full-image edges
        
        // ==== ROI PROCESSING ====
        Rect roi(0, image.rows - 110, image.cols, 110);
        Mat road_region = image(roi);
        
        // Blur + Edge detection in ROI
        Mat blurred, edges_roi;
        GaussianBlur(road_region, blurred, Size(5,5), 1.5);
        Canny(blurred, edges_roi, 50, 150, 3);
        
        // ==== LINE DETECTION ====
        vector<Vec4i> lines;
        HoughLinesP(edges_roi, lines, 1, CV_PI/180, 50, 30, 10);
        
        // ==== CREATE OUTPUT ====
        Mat output;
        cvtColor(edges_full, output, COLOR_GRAY2BGR); // Convert edges to 3-channel
        
        // Draw filtered lines (adjusted to full image coordinates)
        for(const auto& l : lines) {
            double angle = abs(atan2(l[3]-l[1], l[2]-l[0]) * 180/CV_PI);
            if(angle > 15 && angle < 75) {
                line(output, 
                    Point(l[0], l[1] + roi.y),  // Adjust Y-coordinate
                    Point(l[2], l[3] + roi.y), 
                    Scalar(0,0,255), 2); // Red lines
            }
        }
        
        imwrite("final_output.jpg", output);
        imshow("Road Edges with Detected Lines", output);
        waitKey(0);
    }
    
};
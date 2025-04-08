#include <systemc>
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <opencv2/opencv.hpp>

using namespace sc_core;

struct Processor1 : sc_module {
    tlm_utils::simple_initiator_socket<Processor1> socket;

    SC_CTOR(Processor1) {
        SC_THREAD(process);
    }

    void process() {
        cv::Mat image = cv::imread("road.jpg", cv::IMREAD_GRAYSCALE);
        if (image.empty()) {
            std::cerr << "Error: Could not read road.jpg" << std::endl;
            return;
        }
    
        int width = image.cols;
        int height = image.rows;
        int type = image.type();
    
        // Serialize metadata and image
        std::vector<unsigned char> payload;
        payload.resize(sizeof(int) * 3 + image.total());
    
        // Copy metadata: width, height, type
        std::memcpy(payload.data(), &width, sizeof(int));
        std::memcpy(payload.data() + sizeof(int), &height, sizeof(int));
        std::memcpy(payload.data() + 2 * sizeof(int), &type, sizeof(int));
    
        // Copy image data
        std::memcpy(payload.data() + 3 * sizeof(int), image.data, image.total());
    
        // Setup transaction
        tlm::tlm_generic_payload trans;
        sc_time delay = SC_ZERO_TIME;
    
        trans.set_command(tlm::TLM_WRITE_COMMAND);
        trans.set_address(0);
        trans.set_data_ptr(payload.data());
        trans.set_data_length(payload.size());
    
        socket->b_transport(trans, delay);
        std::cout << "Processor1: Image and metadata sent to memory." << std::endl;
    }
    
};
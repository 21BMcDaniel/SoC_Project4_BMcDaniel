#include <systemc>
#include <tlm>
#include <tlm_utils/multi_passthrough_target_socket.h>
#include <vector>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

struct Memory : sc_module {
    tlm_utils::multi_passthrough_target_socket<Memory> socket;
    std::vector<unsigned char> buffer;

    SC_CTOR(Memory) : socket("socket") {
        socket.register_b_transport(this, &Memory::b_transport);
    }

    void b_transport(int id, tlm::tlm_generic_payload& trans, sc_time& delay) {
        unsigned char* ptr = trans.get_data_ptr();
        unsigned int len = trans.get_data_length();
        tlm::tlm_command cmd = trans.get_command();

        if (cmd == tlm::TLM_WRITE_COMMAND) {
            buffer.assign(ptr, ptr + len);
        } else if (cmd == tlm::TLM_READ_COMMAND) {
            std::copy(buffer.begin(), buffer.end(), ptr);
        }

        delay += sc_time(10, SC_NS);
    }
};
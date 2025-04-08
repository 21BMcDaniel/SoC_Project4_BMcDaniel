#include "processor1.cpp"
#include "memory.cpp"
#include "processor2.cpp"

int sc_main(int argc, char* argv[]) {
    Processor1 p1("Processor1");
    Memory mem("Memory");
    Processor2 p2("Processor2");

    p1.socket.bind(mem.socket);
    p2.socket.bind(mem.socket);

    sc_start();
    return 0;
}
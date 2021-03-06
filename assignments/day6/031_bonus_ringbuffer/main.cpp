#include "ringbuffer.hpp"

int main() {
    Ringbuffer<int, 3> buf;
    buf.add(1);
    buf.add(2);
    buf.add(3);
    buf.add(4);

    std::cout << "1: " << buf.get() << std::endl;
    std::cout << "2: " << buf.get() << std::endl;
    std::cout << "3: " << buf.get() << std::endl;
    std::cout << "4: " << buf.get() << std::endl;

    buf.add(5);
    buf.add(6);

    std::cout << "==============================" << std::endl;
    std::cout << "1: " << buf.get() << std::endl;
    std::cout << "2: " << buf.get() << std::endl;
    std::cout << "3: " << buf.get() << std::endl;
    std::cout << "4: " << buf.get() << std::endl;

    return 0;
}
//#include "vehicle.hpp"
#include "user_input.hpp"
// #include "can_reader.hpp"
// #include "ringbuffer.hpp"
#include <iostream>
#include "can_buffer.hpp"
#include "socketcan.h"
#include "drivetrain_input_reader.hpp"
#include <thread>

int main() {

    DriveTrainReader reader;

    if (!reader.Initialize("vcan0")) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        //TODO exit all objects gracefully
        return 1;
    }

    while (1) { // main thread will run the simulation
        std::cout << "Acc: " << static_cast<int>(CanBuffer::getInstance().pull().acc) << std::endl;
    }
}
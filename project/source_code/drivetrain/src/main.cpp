#include "vehicle.h"
#include "user_input.h"
#include <iostream>
#include "can_buffer.h"
#include "socketcan.h"
#include "drivetrain_input_reader.h"
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
        std::cout << "Acc: " << static_cast<int>(CanBuffer::GetInstance().Pull().accelerator_pedal) << std::endl;
        for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
    }
}
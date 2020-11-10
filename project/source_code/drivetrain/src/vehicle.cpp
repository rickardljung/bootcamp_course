#include "vehicle.h"
#include <iostream>
#include <thread>

Vehicle::Vehicle(scpp::SocketCan *socket) {
    this->socket = socket;
    this->Run();
}

void Vehicle::Run() {
    const uint8_t msg_id = 2;
    const uint8_t msg_len = 1;
    //payload to be sent in canframe
    uint8_t payload[msg_len];

    bool simulation_running = true;
    while(simulation_running) {
        uint8_t *data =  CanBuffer::GetInstance().Pull();
        UserInput *input = reinterpret_cast<UserInput*>(data);

        if(!input->end_simulation)
        {
            //run simulation
            // payload[0] = input->accelerator_pedal * 2;
            // socket->write(payload, 2, 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        } else
        {
            simulation_running = false;
        }
        /*
        std::cout << "accelerator_pedal: "  << static_cast<int>(input->accelerator_pedal) << std::endl;
        std::cout << "break_pedal: "        << static_cast<int>(data[1]) << std::endl;
        std::cout << "gear_position: "      << static_cast<int>(input->gear_position) << std::endl;
        std::cout << "ignition: "           << static_cast<int>(input->ignition) << std::endl;
        std::cout << "end_simulation: "     << static_cast<int>(input->end_simulation) << std::endl;
        std::cout << "------------------------" << std::endl;
        */

    }
}

//void Vehicle::calculateSpeed() {
    //int rmp = gearbox->getRPM;
    //int hej = engine->gethej;
//}
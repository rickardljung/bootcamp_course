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

    while(this->simulation_running) {
        //get information from buffer
        //run simulation
        //TODO: if statement checking if a "end simulation" is received
        uint8_t *data = (CanBuffer::GetInstance().Pull());
        //int acc_pedal = static_cast<int>(data[0]);

        UserInput *input = reinterpret_cast<UserInput*>(data);

        /*
        arr[0] = acc_value;
        arr[1] = brk_value;
        arr[2] = gear_pos_req;
        arr[3] = ign_req;
        arr[4] = end_sim;


        std::cout << "accelerator_pedal: " << static_cast<int>(input->accelerator_pedal) << std::endl;
        std::cout << "break_pedal: " << static_cast<int>(data[1]) << std::endl;
        std::cout << "gear_position: " << static_cast<int>(input->gear_position) << std::endl;
        std::cout << "ignition: " << static_cast<int>(input->ignition) << std::endl;
        std::cout << "end_simulation: " << static_cast<int>(input->end_simulation) << std::endl;
        std::cout << "------------------------" << std::endl;
        */

        payload[0] = input->accelerator_pedal * 2;
        socket->write(payload, msg_id, msg_len);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

//void Vehicle::calculateSpeed() {
    //int rmp = gearbox->getRPM;
    //int hej = engine->gethej;
//}
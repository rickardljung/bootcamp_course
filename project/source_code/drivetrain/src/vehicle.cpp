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
        int acc_pedal = static_cast<int>(data[0]);
        std::cout << "Acc: " << acc_pedal << std::endl;

        payload[0] = acc_pedal*2;
        socket->write(payload, msg_id, msg_len);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

//void Vehicle::calculateSpeed() {
    //int rmp = gearbox->getRPM;
    //int hej = engine->gethej;
//}
#include "vehicle.h"
#include <iostream>
#include <thread>

/*!
* Reads from the receive buffer, runs the simulation and writes the result to the transmit buffer
* @param socket used for read and write data to can
* @param receive_message_id id of the messages to read
* @param transmit_message_id id of the messages to transmit. 0 if nothing to transmit
*/
void Vehicle::Run() {
    //payload to be sent in canframe
    uint8_t payload[8];

    bool simulation_running = true;
    while(simulation_running) {
        uint8_t *data =  CanBuffer::GetInstance().PullRx();
        UserInput *input = reinterpret_cast<UserInput*>(data);
        if(!input->end_simulation)
        {
            //RUN SIMULATION ENGINE AND GEARBOX
            payload[0] = input->accelerator_pedal * 2;
            CanBuffer::GetInstance().AddTx(payload);
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
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
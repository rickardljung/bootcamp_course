#include "vehicle.h"
#include <iostream>

/*!
* Reads from the receive buffer, runs the simulation and writes the result to the transmit buffer
* @param socket used for read and write data to can
* @param receive_message_id id of the messages to read
* @param transmit_message_id id of the messages to transmit. 0 if nothing to transmit
*/
bool Vehicle::Run() {
    //payload to be sent in canframe
    uint8_t payload[8] = {0,0,0,0,0,0,0,0};
    uint32_t transmit_id = 2;
    uint8_t transmit_length = 1;

    bool return_value = 0;

    CanData data =  CanBuffer::GetInstance().PullRx();
    if (data.id == 1) //can data from input_handler
    {
        UserInput *input = reinterpret_cast<UserInput*>(data.payload);
        if (input->end_simulation) {
            return_value = 0;
        } else
        {
            //RUN SIMULATION ENGINE AND GEARBOX
            payload[0] = input->accelerator_pedal * 2;
            CanBuffer::GetInstance().AddTx(&transmit_id, payload, &transmit_length);
            return_value = 1;
        }
    }
    return return_value;
}
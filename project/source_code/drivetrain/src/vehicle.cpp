#include "vehicle.h"
#include <iostream>

/*!
* Pulls a CAN message from the receive buffer, checks the ID of the message and performs actions depending on the message.
* The output data will be put on the transmit buffer.
*/
bool Vehicle::Run()
{
    //payload to be sent in canframe
    uint8_t payload[8] = {0,0,0,0,0,0,0,0};
    bool return_value = 1;
    uint8_t vehicle_speed;

    CanData data =  CanBuffer::GetInstance().PullRx();
    if (data.id == 1) //can data from input_handler
    {
        UserInput *input = reinterpret_cast<UserInput*>(data.payload);
        if (input->end_simulation) {
            return_value = 0;
        } else
        {
            //RUN SIMULATION ENGINE AND GEARBOX
            //engine.RPM(input->accelerator_pedal, input->brake_pedal);
            gearbox.GearLeverPosition(input->gear_position, this->vehicle_speed, input->brake_pedal);
            gearbox.GearNumber(this->engine.get_eng_rpm());
            //vehicle_speed = this->CalculateVehicleSpeed(input->brake_pedal);
            //engine.ActualRPM(vehicle_speed, this->gearbox.get_gear_ratio());

            /* payload[0] = this->gearbox.get_gear_position();
            payload[1] = static_cast<uint8_t>(this->engine.get_eng_rpm() / (int)37);
            payload[2] = vehicle_speed;
            CanBuffer::GetInstance().AddTx(&transmit_id, payload, &transmit_length); */
            return_value = 1;
        }
    }
    return return_value;
}
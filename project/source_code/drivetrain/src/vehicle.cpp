#include "vehicle.h"
#include <iostream>
#include <math.h>

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
            engine.RPM(input->accelerator_pedal, input->brake_pedal);
            gearbox.GearLeverPosition(input->gear_position, this->vehicle_speed, input->brake_pedal);
            gearbox.GearNumber(this->engine.get_eng_rpm());
            vehicle_speed = this->CalculateVehicleSpeed(input->brake_pedal);
            engine.ActualRPM(vehicle_speed, this->gearbox.get_gear_ratio());

            payload[0] = this->gearbox.get_gear_position();
            payload[1] = static_cast<uint8_t>(this->engine.get_eng_rpm() / (int)37);
            payload[2] = vehicle_speed;
            CanBuffer::GetInstance().AddTx(&transmit_id, payload, &transmit_length);
            return_value = 1;
        }
    }
    return return_value;
}

uint8_t calculate_resistance(uint8_t speed)
{
    return ( 0.00005*(2*pow(speed,2)) + 5 );
}

uint16_t calculate_engine_tq(uint8_t engine_speed)
{
    return ( (-0.00008*(pow(engine_speed,2))+engine_speed)/1000 );
}

uint16_t calculate_brake_tq(uint8_t brake_pedal)
{
    return ( 0.01*brake_pedal );
}

uint8_t Vehicle::CalculateVehicleSpeed(uint8_t brk_pedal)
{
    uint8_t veh_spd =0;
    uint8_t const_factor =0;
    uint16_t veh_accel =0;
    veh_accel = (calculate_engine_tq(this->engine.get_eng_rpm())*(this->gearbox.get_gear_ratio())-calculate_brake_tq(brk_pedal))*(this->tire_diameter)\
                /((this->weight)-(calculate_resistance(veh_spd)));
    veh_spd = (veh_spd+(veh_accel*(0.0000005)));

    // const_factor = (3.6*M_PI*(this->tire_diameter))/(30*(this->diff_ratio));
    // veh_spd = ((this->gearbox.get_gear_ratio())*(this->engine.get_eng_rpm())*const_factor);
    // veh_spd = veh_spd * 0.621371; //MPH


   // veh_spd = veh_spd - calculate_resistance(veh_spd);
   // veh_spd = ((this->engine.get_eng_rpm())*3.6*M_PI*(this->tire_diameter))\
   //         /30*(this->diff_ratio)*(this->gearbox.get_gear_ratio());

    return veh_spd;
}

// Vehicle::Vehicle(void)
// {
//     //std::cout << "Initialization" << std::endl;
//     //Instantiate engine class
//     Engine engine;
//     //Instantiate gearbox class
//     Gearbox gearbox;
// }

    Torque from engine is used to calculate the vehicle acceleration, which is integrated into vehicle speed.
    Acceleration = WheelTorque                           *WheelRadius /VehicleMass - RollingResistance
                 = (EngineTorque*GearRatio - BrakeTorque)*WheelRadius /VehicleMass - VehicleSpeed^2*MagicNumber
    VehicleSpeed = VehicleSpeed + DeltaSpeed
                 = VehicleSpeed + Acceleration*timeStep
    GearboxRPS   = VehicleSpeed / WheelRadius
    EngineRPS    = GearboxRPS * GearRatio * FinalGear
    EngineRPS is used as input to Engine to calculate torque next iteration.
#include "vehicle.h"
#include <iostream>
#include <math.h>

/*!
* Constructor of Vehicle. Assigns the class members.
* @param gearbox gearbox simulation object
* @param engine engine simulation object
*/
Vehicle::Vehicle(Gearbox *_gearbox, Engine *_engine, const float &_diff_ratio, const uint16_t &_weight, const float &_tire_diameter)
                 : gearbox(_gearbox), engine(_engine), diff_ratio(_diff_ratio), weight(_weight), tire_diameter(_tire_diameter) {}

//Number of instructions? In .h file? Only on constructors?

/*     this->gearbox = gearbox;
    this->engine = engine;
    //Define final drive, weight and tire diameter
    this->diff_ratio = diff_ratio;
    this->weight = weight;
    this->tire_diameter = tire_diameter;
}*/
/*!
* Pulls a CAN message from the receive buffer, checks the ID of the message and performs actions depending on the message.
* The output data will be put on the transmit buffer.
*/
bool Vehicle::Run()
{
    //payload to be sent in canframe
    uint8_t payload[8] = {0,0,0,0,0,0,0,0};
    bool return_value = 1;
    float rpm_to_speed_factor;


    CanData data =  CanBuffer::GetInstance().PullRx();
    if (data.id == 1) //can data from input_handler
    {
        UserInput *input = reinterpret_cast<UserInput*>(data.payload);
        if (input->end_simulation) {
            return_value = 0;
        } else
        {
            //RUN SIMULATION ENGINE AND GEARBOX
            this->engine->Ignition(input->ignition, this->vehicle_speed, input->brake_pedal, this->gearbox->get_gear_lever_position());
            this->engine->RPM(input->accelerator_pedal, input->brake_pedal, sampletime_micro);
            this->gearbox->GearLeverPosition(input->gear_position, this->vehicle_speed, input->brake_pedal);
            //if gear number has changed recalc factor and RPM
            if(this->gearbox->GearNumberChange(this->engine->get_eng_rpm()))
            {
                rpm_to_speed_factor = this->RPMToSpeedFactor();
                engine->ActualRPM(this->vehicle_speed, rpm_to_speed_factor);
            }
            else
            {
                rpm_to_speed_factor = this->RPMToSpeedFactor();
            }
            this->VehicleSpeed(input->brake_pedal, rpm_to_speed_factor);
            engine->ActualRPM(this->vehicle_speed, rpm_to_speed_factor);
/*
            std::cout << "RPM: " << this->engine->get_eng_rpm() << std::endl;
            std::cout << "Gear lever position: " << (int)this->gearbox->get_gear_lever_position() << std::endl;
            std::cout << "Gear number: " << (int)this->gearbox->get_gear_number() << std::endl;
            std::cout << "Speed: " << this->vehicle_speed << std::endl << std::endl;
*/

            payload[0] = static_cast<uint8_t>(this->engine->get_eng_sts());
            payload[1] = static_cast<uint8_t>(this->engine->get_eng_rpm()/37);
            payload[2] = static_cast<uint8_t>(vehicle_speed);
            payload[3] = this->gearbox->get_gear_lever_position();
            payload[4] = this->gearbox->get_gear_number();
            CanBuffer::GetInstance().AddTx(&transmit_id, payload, &transmit_length);
            return_value = 1;
        }
    }
    return return_value;
}

void Vehicle::VehicleSpeed(const uint8_t &brk_pedal, const float &rpm_to_speed)
{
    /*float veh_accel =0;
    float Engine_torque = 0;
    float Gear_ratios = 0;
    float Brake_torque = 0;
    float constant_to_RPM = 0;
    float const_factor = 0;
    */

    //To be removed once the code above works
    if(this->gearbox->get_gear_lever_position() == D||this->gearbox->get_gear_lever_position() == R)
    {

        this->vehicle_speed = ((this->engine->get_eng_rpm())*rpm_to_speed)-
                                (calculate_brake_tq(brk_pedal))-
                                calculate_resistance(this->weight, this->vehicle_speed);
        if(this->vehicle_speed < 7 && brk_pedal > 0)
        {
            this->vehicle_speed = 0;
        }
    //  veh_spd = veh_spd * 0.621371; //MPH


    // veh_spd = veh_spd - calculate_resistance(veh_spd);
    // veh_spd = ((this->engine.get_eng_rpm())*3.6*M_PI*(this->tire_diameter))\
    //         /30*(this->diff_ratio)*(this->gearbox.get_gear_ratio());
    }



// To be removed once the code works
    // Torque from engine is used to calculate the vehicle acceleration, which is integrated into vehicle speed.
    // Acceleration = WheelTorque                           *WheelRadius /VehicleMass - RollingResistance
    //              = (EngineTorque*GearRatio - BrakeTorque)*WheelRadius /VehicleMass - VehicleSpeed^2*MagicNumber
    // VehicleSpeed = VehicleSpeed + DeltaSpeed
    //              = VehicleSpeed + Acceleration*timeStep
    // GearboxRPS   = VehicleSpeed / WheelRadius
    // EngineRPS    = GearboxRPS * GearRatio * FinalGear
    // EngineRPS is used as input to Engine to calculate torque next iteration.


// To be removed used only for testing
    // for(int i=900; i<=9000; i++){
    // veh_accel = (calculate_engine_tq(i)*(2.97)-calculate_brake_tq(0))*(0.680)/((1000)-(calculate_resistance(veh_spd)));
    // veh_spd = (veh_spd+(veh_accel*(0.05)));
    // std::cout << veh_spd << std::endl;
    //     }
    // Engine_torque = (calculate_engine_tq(this->engine->get_eng_rpm()));
    // Gear_ratios = (this->gearbox->get_gear_ratio())*(this->diff_ratio);
    // Brake_torque = calculate_brake_tq(brk_pedal);

    // veh_accel = Engine_torque*Gear_ratios*(this->tire_diameter)/this->weight, this->vehicle_speed));
    // this->vehicle_speed += (veh_accel*sampletime_micro*pow(10,-6)); //needs to be adjusted - 0.0000005 is a constant given from Ludvig

    // std::cout << vehicle_speed << std::endl;

    // constant_to_RPM = (((this->gearbox->get_gear_ratio())*(this->diff_ratio))/(this->tire_diameter))*60;

}

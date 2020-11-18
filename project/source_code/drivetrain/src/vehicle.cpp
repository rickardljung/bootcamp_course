#include "vehicle.h"
#include <iostream>
#include <math.h>

/*!
* Constructor of Vehicle. Assigns the class members.
* @param gearbox gearbox simulation object
* @param engine engine simulation object
*/
Vehicle::Vehicle(Gearbox *gearbox, Engine *engine) {
    this->gearbox = gearbox;
    this->engine = engine;
}
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
            this->engine->Ignition(input->ignition, this->vehicle_speed, input->brake_pedal, this->gearbox->get_gear_lever_position());
            this->engine->RPM(input->accelerator_pedal, input->brake_pedal, sampletime_micro);
            this->gearbox->GearLeverPosition(input->gear_position, this->vehicle_speed, input->brake_pedal);
            this->gearbox->GearNumber(static_cast<uint16_t>(this->engine->get_eng_rpm()));
            vehicle_speed = this->CalculateVehicleSpeed(input->brake_pedal);
            //engine.ActualRPM(vehicle_speed, speed_to_rpm_factor);

            payload[0] = static_cast<uint8_t>(this->engine->get_eng_sts());
            payload[1] = static_cast<uint8_t>(this->engine->get_eng_rpm()/37);
            payload[2] = vehicle_speed;
            CanBuffer::GetInstance().AddTx(&transmit_id, payload, &transmit_length);
            return_value = 1;
        }
    }
    return return_value;
}

//Function used to calculate vehicle rolling resistance depending on veh speed, needs calibration possibly
float calculate_resistance(uint16_t weight, uint8_t speed)
{
    return (weight)-(( 0.00005*(2*pow(speed,2)) + 1 )*10);
}

//Function used to compute engine torque dependent on engine rpm, should be okey without calibraion
float calculate_engine_tq(uint16_t engine_speed)
{
    return ( (-0.00008*(pow(engine_speed,2))+engine_speed)/10 );
}

//Function that mimics brake pedal action, hard to say if it will work without any changes
float calculate_brake_tq(uint8_t brake_pedal)
{
    return ( 0.01*brake_pedal ); //Possibly some factor needed to make it stop, it should make acceleration negative?
}

float Vehicle::CalculateVehicleSpeed(uint8_t brk_pedal)
{
    float veh_accel =0;
    float constant_to_RPM = 0;

// To be removed used only for testing
    // for(int i=900; i<=9000; i++){
    // veh_accel = (calculate_engine_tq(i)*(2.97)-calculate_brake_tq(0))*(0.680)/((1000)-(calculate_resistance(veh_spd)));
    // veh_spd = (veh_spd+(veh_accel*(0.05)));
    // std::cout << veh_spd << std::endl;
    //     }
      
    veh_accel = (calculate_engine_tq(this->gearbox.get_gear_ratio())*((this->gearbox.get_gear_ratio())*(this->diff_ratio))
                 -calculate_brake_tq(brk_pedal))*(this->tire_diameter)
                /(calculate_resistance(this->weight, this->vehicle_speed));
    this->vehicle_speed += (veh_accel*(0.0000005)); //needs to be adjusted - 0.0000005 is a constant given from Ludvig 

    constant_to_RPM = (((this->gearbox.get_gear_ratio())*(this->diff_ratio))/(this->tire_diameter))*60;

//To be removed once the code above works
    // const_factor = (3.6*M_PI*(this->tire_diameter))/(30*(this->diff_ratio));
    // veh_spd = ((this->gearbox.get_gear_ratio())*(this->engine.get_eng_rpm())*const_factor);
    // veh_spd = veh_spd * 0.621371; //MPH


   // veh_spd = veh_spd - calculate_resistance(veh_spd);
   // veh_spd = ((this->engine.get_eng_rpm())*3.6*M_PI*(this->tire_diameter))\
   //         /30*(this->diff_ratio)*(this->gearbox.get_gear_ratio());

    return constant_to_RPM;
}

Vehicle::Vehicle(void)
{
    //Instantiate engine class
    Engine engine;
    //Instantiate gearbox class
    Gearbox gearbox;
    //Define final drive, weight and tire diameter
    this->diff_ratio = 3.42;
    this->weight = 1000;
    this->tire_diameter = 0.680;
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

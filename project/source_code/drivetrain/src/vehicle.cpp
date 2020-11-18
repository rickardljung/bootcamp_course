#include "vehicle.h"
#include <iostream>
#include <math.h>

/*!
* Constructor of Vehicle. Assigns the class members.
* @param gearbox gearbox simulation object
* @param engine engine simulation object
*/
Vehicle::Vehicle(Gearbox *gearbox, Engine *engine, const float &diff_ratio, const uint16_t &weight, const float &tire_diameter) {
    this->gearbox = gearbox;
    this->engine = engine;
    //Define final drive, weight and tire diameter
    this->diff_ratio = diff_ratio;
    this->weight = weight;
    this->tire_diameter = tire_diameter;
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
            //vehicle_speed = this->CalculateVehicleSpeed(input->brake_pedal);
            engine->ActualRPM(this->vehicle_speed, this->CalculateVehicleSpeed(input->brake_pedal));

            payload[0] = static_cast<uint8_t>(this->engine->get_eng_sts());
            payload[1] = static_cast<uint8_t>(this->engine->get_eng_rpm()/37);
            payload[2] = vehicle_speed;
            CanBuffer::GetInstance().AddTx(&transmit_id, payload, &transmit_length);
            return_value = 1;
        }
    }
    return return_value;
}


/*!
* Function used to calculate vehicle rolling resistance 
* depending on veh speed, needs calibration possibly
* @param weight vehicle weight
* @param speed speed of the vehicle
* @return calculated rolling resistance
*/
float calculate_resistance(uint16_t weight, uint8_t speed)
{
    return (weight)+(( 0.00005*(2*pow(speed,2)) + 1 )*100);
}

/*!
* Function used to compute engine torque dependent 
* on engine rpm, should be okey without calibraion
* @param engine_speed RPM of the engine
* @return calculated engine torqe
*/
float calculate_engine_tq(uint16_t engine_speed)
{ //return ( gas_ped * (-0.00008*(pow(engine_speed,2))+engine_speed)/10 );
    return ( (-0.00008*(pow(engine_speed,2))+engine_speed)/10 );
}

/*!
* Function that mimics brake pedal action
* might require calibration
* @param brake_pedal brake pedal position
* @return calculated brake force
*/
float calculate_brake_tq(uint8_t brake_pedal)
{
    return ( 0.01*brake_pedal ); //Possibly some factor needed to make it stop, it should make acceleration negative?
}

/*!
* Function that calculates vehicle acceleration and speed
* @param brake_pedal brake pedal position
* @return calculated constant parapeter that can be used in the engine to 
*/
float Vehicle::CalculateVehicleSpeed(uint8_t brk_pedal)
{
    float veh_accel =0;
    float Engine_torque = 0;
    float Gear_ratios = 0;
    float Brake_torque = 0;
    float constant_to_RPM = 0;
    float const_factor = 0;


//To be removed once the code above works
if(this->gearbox->get_gear_lever_position() == D||this->gearbox->get_gear_lever_position() == R)
{

    const_factor = ((3.6*M_PI*(this->tire_diameter))/(this->gearbox->get_gear_ratio()*60*(this->diff_ratio)))*0.621371;
    
    this->vehicle_speed = ((this->engine->get_eng_rpm())*const_factor)-(calculate_brake_tq(brk_pedal)); //sampletime_micro*pow(10,-6)*
    
  //  veh_spd = veh_spd * 0.621371; //MPH

    std::cout << this->vehicle_speed << std::endl;

   // veh_spd = veh_spd - calculate_resistance(veh_spd);
   // veh_spd = ((this->engine.get_eng_rpm())*3.6*M_PI*(this->tire_diameter))\
   //         /30*(this->diff_ratio)*(this->gearbox.get_gear_ratio());
}
    return const_factor;
    std::cout << vehicle_speed << std::endl;

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
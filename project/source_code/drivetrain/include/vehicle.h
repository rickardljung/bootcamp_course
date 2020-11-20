#ifndef VEHICLE_H
#define VEHICLE_H
#include "engine_simulator.h"
#include "gearbox_simulator.h"
#include "user_input.h"
#include "can_buffer.h"
#include <thread>

const uint32_t transmit_id = 2;
const uint8_t transmit_length = 5;
const uint16_t sampletime_micro = 5;

class Vehicle {
    private:
        Engine *engine;
        Gearbox *gearbox;
        float tire_diameter;
        float diff_ratio;
        uint16_t weight;
        float vehicle_speed=0;
    public:
        Vehicle(Gearbox *gearbox, Engine *engine, const float &diff_ratio, const uint16_t &weight, const float &tire_diameter);
        float RPMToSpeedFactor();
        void VehicleSpeed(const uint8_t &brk_pedal, const float &rpm_to_speed);
        bool Run();
};
/*!
* Function used to calculate vehicle rolling resistance
* depending on veh speed, needs calibration possibly
* @param weight vehicle weight
* @param speed speed of the vehicle
* @return calculated rolling resistance
*/
inline float calculate_resistance(uint16_t weight, float speed)
{
    //return (weight)+(( 0.00005*(2*pow(speed,2)) + 1 )*100);
    return weight*speed*sampletime_micro*3*pow(10, -9);
}

/*!
* Function used to compute engine torque dependent
* on engine rpm, should be okey without calibraion
* @param engine_speed RPM of the engine
* @return calculated engine torqe
*/
inline float calculate_engine_tq(uint16_t engine_speed)
{ //return ( gas_ped * (-0.00008*(pow(engine_speed,2))+engine_speed)/10 );
    return ( (-0.00008*(pow(engine_speed,2))+engine_speed)/10 );
}

/*!
* Function that mimics brake pedal action
* might require calibration
* @param brake_pedal brake pedal position
* @return calculated brake force
*/
inline float calculate_brake_tq(uint8_t brake_pedal)
{
    return sampletime_micro*pow(10, -6)*((5*brake_pedal)); //Possibly some factor needed to make it stop, it should make acceleration negative?
}

/*!
* Function that calculates vehicle acceleration and speed
* @param brake_pedal brake pedal position
* @return calculated constant parapeter that can be used in the engine to
*/

inline float Vehicle::RPMToSpeedFactor()
{
    return (((3.6*M_PI*(this->tire_diameter))/(this->gearbox->get_gear_ratio()*60*(this->diff_ratio)))*0.621371);
}

#endif


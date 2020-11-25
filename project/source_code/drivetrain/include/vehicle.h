#ifndef VEHICLE_H
#define VEHICLE_H
#include <thread>
#include <math.h>
#include "engine_simulator.h"
#include "gearbox_simulator.h"
#include "user_input.h"
#include "can_buffer.h"

const uint32_t transmit_id = 2;
const uint8_t transmit_length = 5;
const uint16_t sampletime_micro = 5;

typedef struct xc60_struct {
    const float diff_ratio = 3.42;
    const float weight = 1000;
    const float tire_diameter = 0.680;
    const uint16_t engine_horsepower = 1000;
    const uint16_t engine_max_rpm = 9000;
    const float gear_ratios[7] = {3.00, 3.50, 2.56, 1.88, 1.35, 1.00, 0.83};
    const uint8_t gear_ratios_size = 7;
} VolvoXC60;

typedef struct v90_struct {
    const float diff_ratio = 3.42;
    const float weight = 1000;
    const float tire_diameter = 0.680;
    const uint16_t engine_horsepower = 1000;
    const uint16_t engine_max_rpm = 9000;
    const float gear_ratios[7] = {3.00, 3.50, 2.56, 1.88, 1.35, 1.00, 0.83};
    const uint8_t gear_ratios_size = 7;
} VolvoV90;

template <typename T>
class Vehicle {
    private:
        Engine engine;
        Gearbox gearbox;
        float vehicle_speed = 0;
        const T veh_spec;
    public:
        Vehicle();
        float RPMToSpeedFactor();
        void VehicleSpeed(const uint8_t &brk_pedal, const float &rpm_to_speed);
        bool Run();
};

/*!
* Constructor of Vehicle. Assigns the class members and initialized engine and gearbox
* @param gearbox gearbox simulation object
* @param engine engine simulation object
*/
template <typename T>
Vehicle<T>::Vehicle() {
    engine.initialize(this->veh_spec.engine_horsepower, this->veh_spec.engine_max_rpm);
    gearbox.initialize(this->veh_spec.gear_ratios, this->veh_spec.gear_ratios_size);
}

/*!
* Pulls a CAN message from the receive buffer, checks the ID of the message and performs actions depending on the message.
* The output data will be put on the transmit buffer.
*/
template <typename T>
bool Vehicle<T>::Run()
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
            this->engine.Ignition(input->ignition, this->vehicle_speed, input->brake_pedal, this->gearbox.get_gear_lever_position());
            this->engine.RPM(input->accelerator_pedal, input->brake_pedal, sampletime_micro);
            this->gearbox.GearLeverPosition(input->gear_position, this->vehicle_speed, input->brake_pedal);
            //if gear number has changed recalc factor and RPM
            if(this->gearbox.GearNumberChange(this->engine.get_eng_rpm()))
            {
                rpm_to_speed_factor = this->RPMToSpeedFactor();
                engine.ActualRPM(this->vehicle_speed, rpm_to_speed_factor);
            }
            else
            {
                rpm_to_speed_factor = this->RPMToSpeedFactor();
            }
            this->VehicleSpeed(input->brake_pedal, rpm_to_speed_factor);
            engine.ActualRPM(this->vehicle_speed, rpm_to_speed_factor);

            std::cout << "RPM: " << this->engine.get_eng_rpm() << std::endl;
            std::cout << "Gear lever position: " << (int)this->gearbox.get_gear_lever_position() << std::endl;
            std::cout << "Gear number: " << (int)this->gearbox.get_gear_number() << std::endl;
            std::cout << "Speed: " << this->vehicle_speed << std::endl << std::endl;


            payload[0] = static_cast<uint8_t>(this->engine.get_eng_sts());
            payload[1] = static_cast<uint8_t>(this->engine.get_eng_rpm()/37);
            payload[2] = static_cast<uint8_t>(vehicle_speed);
            payload[3] = this->gearbox.get_gear_lever_position();
            payload[4] = this->gearbox.get_gear_number();
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
inline float calculate_resistance(uint16_t weight, float speed)
{
    return weight*speed*sampletime_micro*3*pow(10, -9);
}

/*!
* Function used to compute engine torque dependent
* on engine rpm, should be okey without calibraion
* @param engine_speed RPM of the engine
* @return calculated engine torqe
*/
inline float calculate_engine_tq(uint16_t engine_speed)
{
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
    return sampletime_micro*pow(10, -6)*((5*brake_pedal));
}

/*!
* Function that calculates vehicle acceleration and speed
* @param brake_pedal brake pedal position
* @return calculated constant parapeter that can be used in the engine to
*/
template <typename T>
inline float Vehicle<T>::RPMToSpeedFactor()
{
    return (((3.6*M_PI*(veh_spec.tire_diameter))/(this->gearbox.get_gear_ratio()*60*(veh_spec.diff_ratio)))*0.621371);
}

/*!
* Function that calculates vehicle acceleration and speed
* @param brake_pedal brake pedal position
* @return calculated constant parapeter that can be used in the engine to
*/
template <typename T>
void Vehicle<T>::VehicleSpeed(const uint8_t &brk_pedal, const float &rpm_to_speed)
{
    if(this->gearbox.get_gear_lever_position() == D||this->gearbox.get_gear_lever_position() == R)
    {

        this->vehicle_speed = ((this->engine.get_eng_rpm())*rpm_to_speed)-
                                (calculate_brake_tq(brk_pedal))-
                                calculate_resistance(veh_spec.weight, this->vehicle_speed);
        if(this->vehicle_speed < 7 && brk_pedal > 0)
        {
            this->vehicle_speed = 0;
        }
    }
}

typedef Vehicle<VolvoXC60> myVolvoXC60;
typedef Vehicle<VolvoV90> myVolvoV90;

#endif
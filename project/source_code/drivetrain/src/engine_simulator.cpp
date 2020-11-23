#include "engine_simulator.h"

/*!
	* Initializes Engine, sets horsepower and max rpm.
    * @param hp horsepower.
    * @param max_rpm maximum RPM.
*/
void Engine::initialize(const uint16_t &hp, const uint16_t &max_rpm)
{
    this->eng_hp = hp;
    this->eng_max_rpm = max_rpm;
}

/*!
	* Determines if engine should be on or off.
    * @param ign_req ignition request from user.
    * @param speed current vehicle speed.
    * @param brk_pedal % that the brake pedal is pressed.
    * @param gear_position current gear lever position.
*/
void Engine::Ignition(const bool &ign_req, const uint8_t &speed, const uint8_t &brk_pedal, const uint8_t &gear_position)
{
    if(ign_req && !this->eng_sts && (speed > 0 || brk_pedal > 0) &&
        (gear_position == gear_lever_position::P ||
            gear_position == gear_lever_position::N))
    {
        this->eng_sts = true;
    }
    else if(!ign_req && this->eng_sts && speed == 0 &&
            (gear_position == gear_lever_position::P ||
                gear_position == gear_lever_position::N))
    {
        this->eng_sts = false;
    }
}

/*!
	* Increases RPM based on user input. Checks that we dont exceed max RPM.
    * @param acc_pedal % that the acceleration pedal is pressed.
    * @param brk_pedal % that the brake pedal is pressed.
*/
void Engine::RPM(const uint8_t &acc_pedal, const uint8_t &brk_pedal, const uint16_t &sampletime)
{
    if(this->eng_sts)
    {
        //if RPM = 0 (engine was just started), set idle RPM
        if(this->eng_rpm == 0)
        {
            this->eng_rpm = eng_idle_rpm;
        }
        //if acc pedal is pressed and brake is not, increase rpm based on how much it is pressed
        if(acc_pedal > 0 && brk_pedal == 0)
        {
            this->eng_rpm+= acc_pedal*this->eng_hp*sampletime*rpm_simulation_constant;
        }
        //if RPM is max decrease RPM by rpm_max_dec
        if(this->eng_rpm > this->eng_max_rpm)
        {
            this->eng_rpm -= this->rpm_max_dec;
        }
    }
    //if engine is off set 0 rpm
    else
    {
        this->eng_rpm = 0;
    }
}

/*!
	* Calculates actual RPM based on speed and speed to rpm factor.
    * @param speed current vehicle speed.
    * @param speed_to_rpm_factor factor to multiply with speed to receive actual RPM.
*/
void Engine::ActualRPM(const float &speed, const float &speed_to_rpm_factor)
{
    if(this->eng_sts)
    {
        //calculate actual RPM
        this->eng_rpm = speed/speed_to_rpm_factor;

        //if RPM is below idle set idle
        if(this->eng_rpm < this->eng_min_rpm)
        {
            this->eng_rpm = this->eng_idle_rpm;
        }
    }
    else
    {
        this->eng_rpm = 0;
    }


    //check if rpm is high enough to shift gear in here or gearbox?

}

/*!
	* Get function for engine RPM.
    * @return current RPM.temp_float_rpm
*/
float Engine::get_eng_rpm()
{
    return this->eng_rpm;
}

/*!
	* Get function for engine status.
    * @return current engine status.
*/
bool Engine::get_eng_sts()
{
    return this->eng_sts;
}

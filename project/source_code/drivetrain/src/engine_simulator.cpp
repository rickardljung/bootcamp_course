#include <iostream>
#include "engine_simulator.h"
#include "user_input.h"


/*!
	* Constructor for Engine, sets horsepower and max rpm.
    * @param hp horsepower.
    * @param max_rpm maximum RPM.
*/
Engine::Engine(uint16_t hp, uint16_t max_rpm)
{
    this->eng_hp = hp;
    this->eng_max_rpm = max_rpm;
}

/*!
	* Calculates actual RPM based on speed and ratios.
    * @param speed current vehicle speed.
    * @param calc_const constant calculated by vehicle based on ratios.
*/
void Engine::ActualRPM(uint8_t speed, double speed_to_rpm_factor)
{
    if(this->eng_sts)
    {
        //calculate actual RPM
        this->temp_rpm = speed*speed_to_rpm_factor;

        //if RPM is below idle set idle
        if(this->temp_rpm < this->eng_idle_rpm)
        {
            this->temp_rpm = this->eng_idle_rpm;
        }
    }
    else
    {
        this->temp_rpm = 0;
    }

    this->eng_rpm = this->temp_rpm;

}

/*!
	* Determines if engine should be on or off.
    * @param ign_req ignition request from user.
    * @param speed current vehicle speed.
    * @param brk_pedal % that the brake pedal is pressed.
    * @param gear_position current gear lever position.
*/
void Engine::Ignition(bool ign_req, uint8_t speed, uint8_t brk_pedal, uint8_t gear_position)
{
    if(ign_req && !this->eng_sts && (speed > 0 || brk_pedal > 0) && (gear_position == P || gear_position == N))
    {
        this->eng_sts = true;
    }
    else if(!ign_req && this->eng_sts && speed == 0 && (gear_position == P || gear_position == N))
    {
        this->eng_sts = false;
    }
}

/*!
	* Increases RPM based on user input. Checks that we dont exceed max RPM.
    * @param acc_pedal % that the acceleration pedal is pressed.
    * @param brk_pedal % that the brake pedal is pressed.
*/
void Engine::RPM(uint8_t acc_pedal, uint8_t brk_pedal, uint16_t sampletime)
{
    if(this->eng_sts == true)
    {
        //check if engsts is on, if RPM = 0 set idle RPM
        if(!this->temp_rpm)
        {
            this->temp_rpm = eng_idle_rpm;
        }
        //if acc pedal is pressed and brake is not, increase rpm based on how much it is pressed
        if(acc_pedal > 0 && brk_pedal == 0)
        {
            this->temp_rpm+= acc_pedal*this->eng_hp*sampletime*0.0000001;
        }
        //if RPM is max decrease RPM by rpm_max_dec
        if(this->temp_rpm > this->eng_max_rpm)
        {
            this->temp_rpm-= this->rpm_max_dec;
        }
    }
    //if engine is off set 0 rpm
    else
    {
        this->temp_rpm = 0;
    }
    this->eng_rpm = this->temp_rpm;
}

/*!
	* Get function for engine RPM.
    * @return current RPM.
*/
uint16_t Engine::get_eng_rpm()
{
    return this->eng_rpm;
}

/*!
	* Get function for engine status.
    * @return current engine status.
*/
uint8_t Engine::get_eng_sts()
{
    return this->eng_sts;
}

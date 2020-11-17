#include "engine_simulator.h"
Engine::Engine(uint16_t hp, uint16_t max_rpm)
{
    this->eng_hp = hp;
    this->eng_max_rpm = max_rpm;
}
void Engine::ActualRPM(uint8_t speed, double gear_ratio){}
void Engine::Ignition(bool ign_req, uint8_t speed, uint8_t brk_pedal, uint8_t gear_position){}


void Engine::RPM(uint8_t acc_pedal, uint8_t brk_pedal)
{
    //if ignition request is on, check if engsts is on, if not start vehicle and set idle RPM
    if(this->eng_sts == true)
    {
        //if acc pedal is pressed and brake is not -> increase rpm based on how much it is pressed
        if(acc_pedal > 0 && brk_pedal == 0)
        {
        this->eng_rpm+= acc_pedal*this->eng_hp*0.01;
        }
        else
        //if acc pedal is not pressed reduce rpm
        {
            this->eng_rpm-= 1;
        }
        //if RPM is max decrease RPM by rpm_max_dec
        if(this->eng_rpm > this->eng_max_rpm)
        {
            this->eng_rpm-= this->rpm_max_dec;
        }
        //if RPM is below idle increase RPM by rpm_min_inc
        if(this->eng_rpm < this->eng_idle_rpm)
        {
            this->eng_rpm+= this->rpm_min_inc;
        }
    }
    //if engine is off set 0 rpm
    else
    {
        this->eng_rpm = 0;
    }
}
uint16_t Engine::get_eng_rpm()
{
    return this->eng_rpm;
}
uint8_t Engine::get_eng_sts()
{
    return this->eng_sts;
}
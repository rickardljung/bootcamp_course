#include "engine_simulator.h"

void Engine::Run(UserInput *input)
{   
    //if ignition request is on, check if engsts is on, if not start vehicle and set idle RPM
    if(input->ignition)
    {
        if(this->eng_sts == Off)
        {
            this->eng_sts = On;
            this->eng_rpm = 900;
        }
        else
        {
            //if acc pedal is pressed and brake is not -> increase rpm based on how much it is pressed
            if(input->accelerator_pedal > 0 && input->brake_pedal == 0)
            {
                this->eng_rpm+= input->accelerator_pedal*0.3;
            }
            else
            //if acc pedal is not pressed reduce rpm
            {
                this->eng_rpm-= 15;
            }
            
        }
        //if gear = max and RPM is max decrease RPM by X
        if(this->eng_rpm > 9000)
        {
            this->eng_rpm-= 300;
        }
        //if gear = min and RPM is below min set RPM to idle
        if(this->eng_rpm < 900)
        {
            this->eng_rpm+= 50;
        }
        

    }
    //if ignition request is off, set engsts = off and RPM = 0
    else
    {
        this->eng_sts = Off;
        this->eng_rpm = 0;
    }
    
    
    //check if rpm is high enough to shift gear in here or gearbox?
    
}
uint16_t Engine::get_rpm()
{
    return this->eng_rpm;
}
uint8_t Engine::get_sts()
{
    return this->eng_sts;
}
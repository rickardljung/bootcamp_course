#include "gearbox_simulator.h"

/*!
* Constructor of Gearbox. Assigns the class members.
* @param gear_ratio gear ratio for each gear. Index representing the gear where
* index 0 specifies gear ratio for reverse
* @param gear_ratio_size the number of elements in gear_ratio
*/
Gearbox::Gearbox(double *gear_ratio, const uint8_t &gear_ratio_size)
{
    this->gear_ratio = gear_ratio;
    this->max_gear_number = gear_ratio_size - 1; //-1 since reverse is included
    this->gear_lever_position = P;
    this->gear_number = 1;
}
/*!
* Checks if a gear lever position switch should be performed.
* Switches if conditions are fulfilled and sets the gear number.
* @param gear_position_request gear lever position request by user
* @param speed speed of the vehicle
* @param brake_pedal brake pedal position request by user. 0-100%
*/
void Gearbox::GearLeverPosition(const uint8_t &gear_position_request, const uint8_t &speed, const uint8_t &brake_pedal)
{
    //only change if brake is pressed and speed = 0. TODO: make it possible to change to N in speed?
    if(brake_pedal >= break_position_to_change_gear_lever &&
       this->gear_lever_position != gear_position_request && speed == 0)
    {
        this->gear_lever_position = gear_position_request;

        if(this->gear_lever_position == R)
        {
            this->gear_number = 0;
        } else
        {
            this->gear_number = 1;
        }
    }
}
/*!
* Checks if a gear number switch should be performed based on egine RPM.
* Switches if conditions are fulfilled
* @param engine_rpm engine RPM
*/
bool Gearbox::GearNumberChange(const float &engine_rpm)
{
    bool gear_number_change = false;
    if (this->gear_lever_position == D) //TODO: should D be a global parameter?
    {
        if(engine_rpm >= this->RPM_to_increase_gear_number && this->gear_number != this->max_gear_number)
        {
            this->gear_number += 1;
            gear_number_change = true;
        } else if(engine_rpm <= this->RPM_to_decrease_gear_number && this->gear_number != 1)
        {
            this->gear_number -= 1;
            gear_number_change = true;
        }
    }
    return gear_number_change;
}
/*!
* Get function for gear lever position (P = 0, N = 1, D = 2, R = 3)
* @return engaged gear lever position
*/
uint8_t Gearbox::get_gear_lever_position()
{
    return this->gear_lever_position;
}
/*!
* Get function for gear number (1, 2, 3, ...)
* @return engaged gear number
*/
uint8_t Gearbox::get_gear_number()
{
    return this->gear_number;
}
/*!
* Get function for gear ratio.
* @return gear ratio for the engaged gear number
*/
double Gearbox::get_gear_ratio()
{
    return this->gear_ratio[this->gear_number];
}

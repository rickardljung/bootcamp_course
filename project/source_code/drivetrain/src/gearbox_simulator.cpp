#include "gearbox_simulator.h"

Gearbox::Gearbox(double *gear_ratio, uint8_t nbr_gears)
{
    this->gear_ratio = new std::pair<uint8_t, double>[nbr_gears];
}

void Gearbox::GearLeverPosition(uint8_t gear_pos_req, uint8_t speed, uint8_t brk_pedal)
{
    if(brk_pedal > break_position_gear)
    {

    }
}

Gearbox::~Gearbox()
{
    delete this->gear_ratio;
}
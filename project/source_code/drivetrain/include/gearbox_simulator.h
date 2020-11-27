#ifndef GEARBOX_SIMULATOR_H
#define GEARBOX_SIMULATOR_H
#include "user_input.h"

namespace gearbox_constants
{
    const uint8_t break_position_to_change_gear_lever = 10;
    const uint16_t RPM_to_increase_gear_number = 6000;
    const uint16_t RPM_to_decrease_gear_number = 3500;
    //TODO: in a bigger project with more constants would it be a good idea to make gearbox and
    //engine templates. Input to the templates could then be a struct with the constants.
}

class Gearbox {
    private:
        const float *gear_ratio;
        uint8_t gear_lever_position;
        uint8_t gear_number;
        uint8_t max_gear_number;
    public:
        Gearbox() = default;
        void initialize(const float gear_ratio[], const uint8_t &gear_ratio_size);
        ~Gearbox() = default;
        void GearLeverPosition(const uint8_t &gear_position_request, const uint8_t &speed, const uint8_t &brake_pedal);
        bool GearNumberChange(const float &engine_rpm);
        float get_gear_ratio();
        uint8_t get_gear_lever_position();
        uint8_t get_gear_number();
};

/*!
* Get function for gear lever position (P = 0, N = 1, D = 2, R = 3)
* @return engaged gear lever position
*/
inline uint8_t Gearbox::get_gear_lever_position()
{
    return this->gear_lever_position;
}

#endif

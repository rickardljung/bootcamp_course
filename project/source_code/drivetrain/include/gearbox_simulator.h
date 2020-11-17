#ifndef GEARBOX_SIMULATOR_H
#define GEARBOX_SIMULATOR_H
#include <map>
#include "user_input.h"

class Gearbox {
    private:
        double *gear_ratio;
        uint8_t gear_lever_position;
        uint8_t gear_number;
        uint8_t max_gear_number;

        const uint8_t break_position_to_change_gear_lever = 10;
        const uint16_t RPM_to_increase_gear_number = 5000;
        const uint16_t RPM_to_decrease_gear_number = 2000;
    public:
        Gearbox(double *gear_ratio, uint8_t nbr_of_gears);
        ~Gearbox() = default;
        void GearLeverPosition(uint8_t gear_position_request, uint8_t speed, uint8_t brake_pedal);
        void GearNumber(uint16_t engine_rpm);
        double get_gear_ratio();
        uint8_t get_gear_lever_position();
        uint8_t get_gear_number();
};

#endif
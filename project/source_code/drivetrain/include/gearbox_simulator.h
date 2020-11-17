#ifndef GEARBOX_SIMULATOR_H
#define GEARBOX_SIMULATOR_H
#include <map>

class Gearbox {
    private:
        std::pair<uint8_t, double> *gear_ratio;
        uint8_t gear_lever_position;
        const uint8_t break_position_gear
    public:
        Gearbox(double *gear_ratio, uint8_t nbr_gears);
        ~Gearbox(); //delete pair
        void GearLeverPosition(uint8_t gear_pos_req, uint8_t speed, uint8_t brk_pedal);
        void GearNumber(uint16_t eng_rpm);
        double get_gear_ratio();
        uint8_t get_gear_position();
};

#endif
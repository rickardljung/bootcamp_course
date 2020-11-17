#ifndef ENGINE_SIMULATOR_H
#define ENGINE_SIMULATOR_H
#include "user_input.h"


class Engine {
    private:
        bool eng_sts = false;
        uint16_t eng_rpm = 0;
        uint16_t eng_hp;
        uint16_t eng_max_rpm;
        const uint16_t idle_rpm = 900;
    public:
        Engine(uint16_t hp, uint16_t max_rpm);
        void RPM(uint8_t acc_pedal, uint8_t brk_pedal);
        void ActualRPM(uint8_t speed, double gear_ratio);
        void Ignition(bool ign_req, uint8_t speed, uint8_t brk_pedal, uint8_t gear_position);
        uint16_t get_eng_rpm();
        uint8_t get_eng_sts();
};

#endif
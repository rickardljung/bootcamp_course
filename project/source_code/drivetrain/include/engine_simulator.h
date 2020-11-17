#ifndef ENGINE_SIMULATOR_H
#define ENGINE_SIMULATOR_H
#include "user_input.h"


class Engine {
    private:
        bool eng_sts = false;
        float temp_rpm = 0;
        uint16_t eng_rpm = 0;
        uint16_t eng_hp;
        uint16_t eng_max_rpm;
        const uint16_t eng_idle_rpm = 900;
        const uint16_t rpm_max_dec = 300;
        const uint16_t rpm_min_inc = 50;
    public:
        Engine(uint16_t hp, uint16_t max_rpm);
        void RPM(uint8_t acc_pedal, uint8_t brk_pedal, uint16_t sampletime);
        void ActualRPM(uint8_t speed, double calc_const);
        void Ignition(bool ign_req, uint8_t speed, uint8_t brk_pedal, uint8_t gear_position);
        uint16_t get_eng_rpm();
        uint8_t get_eng_sts();
};

#endif
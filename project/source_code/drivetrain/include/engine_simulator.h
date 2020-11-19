#ifndef ENGINE_SIMULATOR_H
#define ENGINE_SIMULATOR_H
#include "user_input.h"
#include <math.h>

enum EngSts : uint8_t {Off = 0, On = 1};

class Engine {
    private:
        bool eng_sts;
        float eng_rpm;
        uint16_t eng_hp;
        uint16_t eng_max_rpm;
        const uint16_t eng_idle_rpm = 900;
        const uint16_t eng_min_rpm = 850;
        const uint16_t rpm_max_dec = 150;
        const float rpm_simulation_constant = 5*pow(10,-7);
    public:
        Engine(const uint16_t &hp, const uint16_t &max_rpm);
        void Ignition(const bool &ign_req, const uint8_t &speed, const uint8_t &brk_pedal, const uint8_t &gear_position);
        void RPM(const uint8_t &acc_pedal, const uint8_t &brk_pedal, const uint16_t &sampletime);
        void ActualRPM(const float &speed, const float &speed_to_rpm_factor);
        float get_eng_rpm();
        bool get_eng_sts();
};

#endif

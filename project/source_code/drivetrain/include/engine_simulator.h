#ifndef ENGINE_SIMULATOR_H
#define ENGINE_SIMULATOR_H
//
#include <math.h>

namespace eng_rpm
{
    const uint16_t idle = 900;
    const uint16_t minimum = 850;
    const uint16_t maximum_decrease = 150;
    const float simulation_constant = 5*pow(10,-7);
}

class Engine {
    private:
        bool eng_sts = false;
        float eng_rpm = 0;
        uint16_t eng_hp;
        uint16_t eng_max_rpm;
    public:
        Engine() = default;
        void initialize(const uint16_t &hp, const uint16_t &max_rpm);
        void Ignition(const bool &ign_req, const uint8_t &speed, const uint8_t &brk_pedal, const uint8_t &gear_position);
        void RPM(const uint8_t &acc_pedal, const uint8_t &brk_pedal, const uint16_t &sampletime);
        void ActualRPM(const float &speed, const float &speed_to_rpm_factor);
        float get_eng_rpm();
        bool get_eng_sts();
};

#endif

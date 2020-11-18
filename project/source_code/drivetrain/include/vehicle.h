#ifndef VEHICLE_H
#define VEHICLE_H
#include "engine_simulator.h"
#include "gearbox_simulator.h"
#include "user_input.h"
#include "can_buffer.h"
#include <thread>

const uint32_t transmit_id = 2;
const uint8_t transmit_length = 2;

class Vehicle {
    private:
        Engine engine;
        Gearbox gearbox;
        double tire_diameter;
        double diff_ratio;
        uint16_t weight;
        double vehicle_speed;
    public:
        Vehicle(); //= default;//TODO: constructor/destructor
        double CalculateVehicleSpeed(uint8_t brk_pedal);
        bool Run();
};

#endif
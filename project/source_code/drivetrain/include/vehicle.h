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
        Gearbox gearbox();
    public:
        Vehicle() = default;
        bool Run();
};

#endif
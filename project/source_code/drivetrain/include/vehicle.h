#ifndef VEHICLE_H
#define VEHICLE_H
#include "engine_simulator.h"
#include "gearbox_simulator.h"
#include "user_input.h"
#include "can_buffer.h"
#include <thread>

class Vehicle {
    private:
        Engine engine;
        Gearbox gearbox();
    public:
        Vehicle() = default;
        bool Initialize();
        void Run();
};

#endif
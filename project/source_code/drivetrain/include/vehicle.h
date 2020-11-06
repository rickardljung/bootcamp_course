#ifndef VEHICLE_H
#define VEHICLE_H
#include "engine_simulator.h"
#include "gearbox_simulator.h"
#include "user_input.h"

class Vehicle {
    private:
        Engine engine();
        Gearbox gearbox();
        bool simulation_running = true;
    public:
        Vehicle() = default;
        void Run();
};

#endif
#ifndef VEHICLE_H
#define VEHICLE_H
#include "engine_simulator.h"
#include "gearbox_simulator.h"
#include "user_input.h"
#include "can_buffer.h"
#include "socketcan.h"

class Vehicle {
    private:
        Engine engine();
        Gearbox gearbox();
        void Run();
        scpp::SocketCan *socket;
    public:
        Vehicle(scpp::SocketCan *socket);
        bool Initialize();
};

#endif
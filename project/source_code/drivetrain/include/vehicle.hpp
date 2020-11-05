#include "engine_simulator.hpp"
#include "gearbox_simulator.hpp"

struct shared_info_struct {
    uint16_t rmp;
} *shared_info;

typedef struct user_input_struct {
    uint8_t acc;
    //etc
} user_input;

class Vehicle {
    private:
        Engine *engine;
        Gearbox *gearbox;
    public:
        Vehicle(user_input *input);
        void run();
};

Vehicle::Vehicle(user_input *input) {
    this->engine = new Engine(user_input, shared_info);
    this->gearbox = new GearBox(user_input, shared_info);
}

void Vehicle::run() {
    while() {
        //get information from buffer
        //run simulation
    }

}

void Vehicle::calculateSpeed() {
    int rmp = gearbox->getRPM;
    int hej = engine->gethej;
}
}
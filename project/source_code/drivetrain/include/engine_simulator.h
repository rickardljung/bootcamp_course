#ifndef ENGINE_SIMULATOR_H
#define ENGINE_SIMULATOR_H
#include "user_input.h"

enum EngSts : uint8_t {Off = 0, On = 1};

class Engine {
    private:
        EngSts eng_sts=Off;
        uint16_t eng_rpm=0;
    public:
        Engine() = default;
        void Run(UserInput *input);
        uint16_t get_rpm();
        uint8_t get_sts();
};

#endif
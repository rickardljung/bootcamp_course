#ifndef KEYBOARD_INPUT_READER_H
#define KEYBOARD_INPUT_READER_H
#include <X11/Xlib.h>
#include <mutex>
#include "user_input.h"

namespace key
{
    const uint8_t escape = 9;
    const uint8_t r = 27;
    const uint8_t p = 33;
    const uint8_t d = 40;
    const uint8_t n = 57;
    const uint8_t up = 111;
    const uint8_t down = 116;
    const uint8_t left = 113;
    const uint8_t right = 114;
    const uint8_t space = 65;
}

class InputReader{
    public:
        InputReader();
        ~InputReader();
        bool Run();
        bool ReadInputs();
        bool InterpretInput();
        void Acceleration();
        void Braking();
        void IgnitionReq();
        void GearPosReq();
        bool EndSimulation();
    private:
        UserInput temp_user_input;
        Display *display;
        Window window;
        XEvent event;
        int s;
};

#endif //KEYBOARD_INPUT_READER_H
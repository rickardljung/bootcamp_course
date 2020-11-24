#ifndef KEYBOARD_INPUT_READER_H
#define KEYBOARD_INPUT_READER_H

#include "user_input.h"
#include "can_buffer.h"

#include <X11/Xlib.h>
#include <mutex>

const unsigned int key_escape = 9;
const unsigned int key_r = 27;
const unsigned int key_p = 33;
const unsigned int key_d = 40;
const unsigned int key_n = 57;
const unsigned int key_h = 43;
const unsigned int key_a = 38;
const unsigned int key_blinker_left = 59;
const unsigned int key_blinker_right = 60;
const unsigned int key_up = 111;
const unsigned int key_down = 116;
const unsigned int key_left = 113;
const unsigned int key_right = 114;
const unsigned int key_space = 65;
const unsigned int acc_inc = 10;
const unsigned int acc_dec = 10;
const unsigned int acc_max = 100;
const unsigned int acc_min = 0;
const unsigned int brk_inc = 20;
const unsigned int brk_dec = 20;
const unsigned int brk_max = 100;
const unsigned int brk_min = 0;


template <typename P>
class InputReader{
    public:
        InputReader(const P& canbuffer);
        ~InputReader();
        bool Run();
        bool ReadInputs();
        bool EndSimulation();
        bool InterpretInput();
        void Braking();
        void Handbrake();
        void GearPosReq();
        void IgnitionReq();
        void HazardLight();
        void Acceleration();
        void LeftBlinkerLight();
        void RightBlinkerLight();
    private:
        UserInput temp_user_input;
        MiscInput user_misc_input;
        Display *display;
        Window window;
        XEvent event;
        P& canbuffer;
        int s;
};

#endif //KEYBOARD_INPUT_READER_H
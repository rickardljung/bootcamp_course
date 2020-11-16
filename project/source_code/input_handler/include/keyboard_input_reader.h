#ifndef KEYBOARD_INPUT_READER_H
#define KEYBOARD_INPUT_READER_H
#include <X11/Xlib.h>
#include <mutex>
#include "user_input.h"

const unsigned int key_escape = 9;
const unsigned int key_r = 27;
const unsigned int key_p = 33;
const unsigned int key_d = 40;
const unsigned int key_n = 57;
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
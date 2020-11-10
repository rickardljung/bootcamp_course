#ifndef KEYBOARD_INPUT_READER_H
#define KEYBOARD_INPUT_READER_H
#include <iostream>
#include <X11/Xlib.h>
#include <atomic>
#include "can_fr_handler.h"


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

struct mykey 
        {
            uint8_t key;
            bool read;
        };
class InputReader{
    public:
        InputReader();
        ~InputReader();
        void Run(uint8_t *arr, UserInput *user_input);
        void ReadInputs();
        void InterpretInput(UserInput *user_input);
        void EncodeArray(uint8_t *arr, UserInput *user_input);
        bool is_running = 0;
    private:
        mykey the_key;
        Display *display;
        Window window;
        XEvent event;
        int s;
};

#endif //KEYBOARD_INPUT_READER_H
#ifndef KEYBOARD_INPUT_READER_H
#define KEYBOARD_INPUT_READER_H
#include <iostream>
#include <X11/Xlib.h>
#include <atomic>

enum GearPos : uint8_t {P=0, N=1, D=2, R=3};
const uint8_t msg_id = 1;
const uint8_t msg_len = 5;

const unsigned int escape = 9;
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
        void Run(uint8_t *arr);
        void ReadInputs();
        void InterpretInput();
        void EncodeArray(uint8_t *arr);
        bool is_running = 0;
    private:
        mykey the_key;
        uint8_t acc_value = 0;
        uint8_t brk_value = 0;
        GearPos gear_pos_req = P;
        uint8_t ign_req = 0;
        uint8_t end_sim = 0;
        Display *display;
        Window window;
        XEvent event;
        int s;
};

#endif //KEYBOARD_INPUT_READER_H
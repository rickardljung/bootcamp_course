#ifndef INPUTREADER_H
#define INPUTREADER_H
#include <iostream>
#include <X11/Xlib.h>

enum GearPos : uint8_t {P=0, N=1, D=2, R=3};
const unsigned int ESCAPE = 9;
const unsigned int key_r = 27;
const unsigned int key_p = 33;
const unsigned int key_d = 40;
const unsigned int key_n = 57;
const unsigned int key_UP = 111;
const unsigned int key_DOWN = 116;
const unsigned int key_LEFT = 113;
const unsigned int key_RIGHT = 114;
const unsigned int key_SPACE = 65;
struct mykey
{
    uint8_t key;
    bool read;

};
class InputReader{
    public:
        InputReader();
        ~InputReader();
        void ReadInputs(struct mykey *K);
        void InterpretInput(struct mykey *K);
        void EncodeArray(uint8_t *arr);
    private:
        uint8_t AccValue = 0;
        uint8_t BrkValue = 0;
        GearPos GearPosReq = P;
        uint8_t IgnReq = 0;
        Display *display;
        Window window;
        XEvent event;
        int s;
};

#endif
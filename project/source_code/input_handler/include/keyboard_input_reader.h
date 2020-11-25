#ifndef KEYBOARD_INPUT_READER_H
#define KEYBOARD_INPUT_READER_H

#include "user_input.h"
#include "can_buffer.h"

#include <mutex>
#include <thread>
#include <cstring>
#include <iostream>
#include <X11/Xlib.h>

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
        InputReader(P& canbuffer);
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
        int s;
        P& canbuffer;
        XEvent event;
        Window window;
        Display *display;
        UserInput temp_user_input;
        MiscInput user_misc_input;
};

/*!
	* Constructor for class InputReader, opens a display and changes settings wanted for the keyboard reading.
    * Sets temp_user_input struct to 0 and adds it to the CAN buffer.
	* @return Nothing is returned
*/
template <typename P>
InputReader<P>::InputReader(P& _canbuffer) : canbuffer(_canbuffer)
{
    /* initialize temp_user_input with 0*/
    std::memset(&temp_user_input,0,sizeof(UserInput));
    /* initialize user_misc_input with 0*/
    std::memset(&user_misc_input,0,sizeof(UserInput));
    /*add empty frame to the CAN buffer*/
    canbuffer.Add(msg_id, reinterpret_cast<uint8_t*>(&temp_user_input), msg_len);
    /* open connection with the server */
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(display);

    /* create window */
    window = XCreateSimpleWindow(display, RootWindow(display, s), 1, 1, 2, 2, 1,
                           BlackPixel(display, s), WhitePixel(display, s));

    /* select kind of events we are interested in */
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask );

    /* map (show) the window */
    XMapWindow(display, window);
    XAutoRepeatOff(display);
}

/*!
	* Runs the main function of InputReader, calls functions ReadInputs and InterpretInput.
    * Adds a message to CanBuffer when input has been read and interpreted.
	* @return Returns True if thread should continue running.
*/
template <typename P>
bool InputReader<P>::Run()
{
    bool return_val = true;
    //interpret user input
    if(ReadInputs())
    {
        return_val = InterpretInput();
        canbuffer.Add(msg_id, reinterpret_cast<uint8_t*>(&temp_user_input), msg_len);
        
      //  std::this_thread::sleep_for(std::chrono::microseconds(200));
        // uint8_t *misc = reinterpret_cast<uint8_t*>(&user_misc_input);
      //  CanBuffer::GetInstance().AddTx(&misc_msg_id, reinterpret_cast<uint8_t*>(&user_misc_input), &misc_msg_len);
    }
    return return_val;
}
/*!
	* Reads inputs from the keyboard (blocking function).
	* @return True if a KeyPress has occurred, false for all other events.
*/
template <typename P>
bool InputReader<P>::ReadInputs()
{
        XNextEvent(display, &event);
        /* keyboard events */
        if(event.type == KeyPress)
        {
            return true;
        }
        return false;

}
/*!
	* Destructor for class InputReader, closes the display and resets settings for the keyboard.
	* @return Nothing is returned
*/
template <typename P>
InputReader<P>::~InputReader()
{
    /* close connection to server */
    XAutoRepeatOn(display);
    XCloseDisplay(display);
}
/*!
	* Decides appropriate action depending on which key was pressed.
	* @return Returns true unless Esc key has been pressed.
*/
template <typename P>
bool InputReader<P>::InterpretInput()
{
    bool return_val = true;
    if(event.xkey.keycode == key_up || event.xkey.keycode == key_down)
    {
        Acceleration();
    }
    else if(event.xkey.keycode == key_left || event.xkey.keycode == key_right)
    {
        Braking();
    }
    else if(event.xkey.keycode == key_p || event.xkey.keycode == key_n ||
             event.xkey.keycode == key_d || event.xkey.keycode == key_r)
    {
        GearPosReq();
    }
    else if(event.xkey.keycode == key_space)
    {
        IgnitionReq();
    }
    else if(event.xkey.keycode == key_escape)
    {
        return_val = EndSimulation();
    }
    else if(event.xkey.keycode == key_h)
    {
        Handbrake();
    }
    else if(event.xkey.keycode == key_a)
    {
        HazardLight();
    }
    else if(event.xkey.keycode == key_blinker_left)
    {
        LeftBlinkerLight();
    }
    else if(event.xkey.keycode == key_blinker_right)
    {
        RightBlinkerLight();
    }
    return return_val;
}
/*!
	* Increases or decreases acceleration value, stores it in temp_user_input.
	* @return Nothing is returned.
*/
template <typename P>
void InputReader<P>::Acceleration()
{
    if(event.xkey.keycode == key_up)
    {
        if(temp_user_input.accelerator_pedal < acc_max)
        {
            temp_user_input.accelerator_pedal+=acc_inc;
        }
    }
    else if(event.xkey.keycode == key_down)
    {
        if(temp_user_input.accelerator_pedal > acc_min)
        {
            temp_user_input.accelerator_pedal-=acc_dec;
        }
    }
}
/*!
	* Increases or decreases brake value, stores it in temp_user_input.
	* @return Nothing is returned.
*/
template <typename P>
void InputReader<P>::Braking()
{
    if(event.xkey.keycode == key_left) //user pressing brake pedal
    {
        if(temp_user_input.brake_pedal < brk_max)
        {
            temp_user_input.brake_pedal+=20;
        }
    }
    else if(event.xkey.keycode == key_right) //user releasing brake pedal
    {
        if(temp_user_input.brake_pedal > brk_min)
        {
            temp_user_input.brake_pedal-=20;
        }
    }
}
/*!
	* Toggles right blinker light indicator on instrument cluster, stores it in user_misc_input.
	* @return Nothing is returned.
*/
template <typename P>
void InputReader<P>::RightBlinkerLight()
{
    user_misc_input.right_blinker = ~user_misc_input.right_blinker;
}
/*!
	* Toggles left blinker light indicator on instrument cluster, stores it in user_misc_input.
	* @return Nothing is returned.
*/
template <typename P>
void InputReader<P>::LeftBlinkerLight()
{
    user_misc_input.left_blinker = ~user_misc_input.left_blinker;
}
/*!
	* Toggles hazard light indicator on instrument cluster, stores it in user_misc_input.
	* @return Nothing is returned.
*/
template <typename P>
void InputReader<P>::HazardLight()
{
    user_misc_input.hazard_light = ~user_misc_input.hazard_light;
}
/*!
	* Toggles handbrake indicator on instrument cluster, stores it in user_misc_input.
	* @return Nothing is returned.
*/
template <typename P>
void InputReader<P>::Handbrake()
{
    user_misc_input.hand_brake = ~user_misc_input.hand_brake;
}
/*!
	* Toggles the ignition request, stores it in temp_user_input.
	* @return Nothing is returned.
*/
template <typename P>
void InputReader<P>::IgnitionReq()
{
    if(temp_user_input.ignition == ignition_on)
    {
        temp_user_input.ignition = ignition_off;
    }
    else
    {
        temp_user_input.ignition = ignition_on;
    }
}
/*!
	* Determines which gear should be requested, stores it in temp_user_input.
	* @return Nothing is returned.
*/
template <typename Y>
void InputReader<Y>::GearPosReq()
{
    if(event.xkey.keycode == key_p)
    {
        temp_user_input.gear_position = P;
    }
    else if(event.xkey.keycode == key_n)
    {
        temp_user_input.gear_position = N;
    }
    else if(event.xkey.keycode == key_d)
    {
        temp_user_input.gear_position = D;
    }
    else if(event.xkey.keycode == key_r)
    {
        temp_user_input.gear_position = R;
    }
}
/*!
	* Sets end simulation.
	* @return Returns false.
*/
template <typename P>
bool InputReader<P>::EndSimulation()
{
    temp_user_input.end_simulation = end;
    return false;
}


#endif //KEYBOARD_INPUT_READER_H
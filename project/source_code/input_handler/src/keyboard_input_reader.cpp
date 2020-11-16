#include "user_input.h"
#include "keyboard_input_reader.h"
#include "can_buffer.h"
#include <iostream>
#include <cstring>

/*!
	* Runs the main function of InputReader, calls functions ReadInputs and InterpretInput.
	* @param user_input fills in values in the user_input struct.
    * @param mtx is the mutex lock used to not write/read to/from user_input struct at the same time from different threads.
	* @return Returns True if thread should continue running.
*/
bool InputReader::Run()
{
    bool return_val = true;
    //interpret user input
    if(ReadInputs())
    {
        return_val = InterpretInput();
        CanBuffer::GetInstance().AddTx(&msg_id, reinterpret_cast<uint8_t*>(&temp_user_input), &msg_len);
    }
    return return_val;
}
/*!
	* Reads inputs from the keyboard (blocking function).
	* @return True if a KeyPress has occurred.
*/
bool InputReader::ReadInputs()
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
InputReader::~InputReader()
{
    /* close connection to server */
    XAutoRepeatOn(display);
    XCloseDisplay(display);
}
/*!
	* Constructor for class InputReader, opens a display and changes settings wanted for the keyboard reading.
	* @return Nothing is returned
*/
InputReader::InputReader()
{
    /* initialize temp_user_input with 0*/
    std::memset(&temp_user_input,0,sizeof(UserInput));
    /*add empty frame to the CAN buffer*/
    CanBuffer::GetInstance().AddTx(&msg_id, reinterpret_cast<uint8_t*>(&temp_user_input), &msg_len);
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
	* Calls functions depending on which key was pressed.
	* @return Returns true unless Esc key has been pressed.
*/
bool InputReader::InterpretInput()
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
    return return_val;
}
/*!
	* Increases or decreases acceleration value, stores it in temp_user_input.
	* @return Nothing is returned.
*/
void InputReader::Acceleration()
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
void InputReader::Braking()
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
	* Toggles the ignition request, stores it in temp_user_input.
	* @return Nothing is returned.
*/
void InputReader::IgnitionReq()
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
void InputReader::GearPosReq()
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
bool InputReader::EndSimulation()
{
    temp_user_input.end_simulation = end;
    return false;
}

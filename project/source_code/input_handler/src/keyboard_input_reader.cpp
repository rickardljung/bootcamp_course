#include "user_input.h"
#include "keyboard_input_reader.h"
#include <iostream>
/*!
	* Runs the main function of InputReader, calls functions ReadInputs and InterpretInput. Exits while loop when esc key is pressed.
	* @param user_input fills in values in the user_input struct.
	* @return Nothing is returned
*/
void InputReader::Run(UserInput *user_input)
{
    is_running = true;
    while(is_running)
    {
        //read user input
        ReadInputs(); 

        //interpret user input
        if(the_key.read == false)
        {
            InterpretInput(user_input);  
        }

        if(the_key.key == key_escape)
        {
            is_running = false;
        }
    }   
}
/*!
	* Reads inputs from keyboard and stores it in the_key (blocking function).
	* @return Nothing is returned
*/
void InputReader::ReadInputs()
{
        XNextEvent(display, &event);
        /* keyboard events */
        if (event.type == KeyPress)
        {
            the_key.key = event.xkey.keycode;
            the_key.read = false;
        }
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
	* Controls what different key presses should be interpreted as. For example pressing "key_up" increases acceleration by 10%.
	* @param user_input values shall be stored in a UserInput struct.
	* @return Nothing is returned
*/
void InputReader::InterpretInput(UserInput *user_input)
{
    
    if(the_key.key == key_up) //user pressing acc pedal
    {
        user_input->accelerator_pedal+=10;
        if(user_input->accelerator_pedal > 100)
        {
            user_input->accelerator_pedal = 100;
        }
        the_key.read = true;
    }
    else if(the_key.key == key_down) //user releasing acc pedal
    {
        user_input->accelerator_pedal-=10;
        if(user_input->accelerator_pedal == 246) // -10 = 246 for uint8
        {
            user_input->accelerator_pedal = 0;
        }
        the_key.read = true;
    }
    else if(the_key.key == key_left) //user pressing brake pedal
    {
        user_input->brake_pedal+=20;
        if(user_input->brake_pedal > 100)
        {
            user_input->brake_pedal = 100;
        }
        the_key.read = true;
    }
    else if(the_key.key== key_right) //user releasing brake pedal
    {
        user_input->brake_pedal-=20;
        if(user_input->brake_pedal == 236) // -20 = 236 for uint8
        {
            user_input->brake_pedal = 0;
        }
        the_key.read = true;
    }
    else if(the_key.key== key_space) //user toggles ignition request
    {
        if(user_input->ignition == 1)
        {
            user_input->ignition = 0;
        }
        else
        {
            user_input->ignition = 1;
        }
        the_key.read = true;
    }
    else if(the_key.key == key_p)
    {
        user_input->gear_position = P;
        the_key.read = true;
    }
    
    else if(the_key.key == key_n)
    {
        user_input->gear_position = N;
        the_key.read = true;
    }
    else if(the_key.key == key_d)
    {
        user_input->gear_position = D;
        the_key.read = true;
    }
    else if(the_key.key == key_r)
    {
        user_input->gear_position = R;
        the_key.read = true;
    }
    else if(the_key.key == key_escape){
        user_input->end_simulation = 1;
        the_key.read = true;
    }
}

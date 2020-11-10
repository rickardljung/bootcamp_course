#include "keyboard_input_reader.h"

void InputReader::Run(uint8_t *arr, UserInput *user_input)
{
    is_running = true;
    while(true)
    {
        //read user input
        ReadInputs(); 

        //interpret user input
        if(the_key.read == false)
        {
            InterpretInput(user_input);  
        }
        //encode into array
        EncodeArray(arr, user_input);

        if(the_key.key == key_escape)
        {
            is_running = false;
            break;
        }
    }
    
}
void InputReader::ReadInputs()
{
        XNextEvent(display, &event);
        /* keyboard events */
        if (event.type == KeyPress)
        {
            //printf( "KeyPress: %x\n", event.xkey.keycode );
            the_key.key = event.xkey.keycode;
            the_key.read = false;
            //std::cout<< "key pressed" << *key << std::endl;
        }
        /*else if (event.type == KeyRelease)
        {
            printf( "KeyRelease: %x\n", event.xkey.keycode );
            returnval = event.xkey.keycode;
        }*/    
}

InputReader::~InputReader()
{
    /* close connection to server */
    XAutoRepeatOn(display);
    XCloseDisplay(display);    
}
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


void InputReader::InterpretInput(UserInput *user_input)
{
    
    if(the_key.key == key_up) //user pressing acc pedal
    {
        user_input->accelerator_pedal+=10;
        //acc_value+=10;
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
    
    /*std::cout << "acc_value: " << (int)acc_value << std::endl;
    std::cout << "brk_value: " << (int)brk_value << std::endl;
    std::cout << "IgnReq: " << (int)IgnReq << std::endl;
    switch (gear_pos_req){
        case(P) :   std::cout << "gear_pos_req: P" << std::endl;
                    break;
        case(N) :   std::cout << "gear_pos_req: N" << std::endl;
                    break;
        case(D) :   std::cout << "gear_pos_req: D" << std::endl;
                    break;
        case(R) :   std::cout << "gear_pos_req: R" << std::endl;
                    break;
    }*/
}

void InputReader::EncodeArray(uint8_t *arr, UserInput *user_input)
{
    arr[0] = user_input->accelerator_pedal;
    arr[1] = user_input->brake_pedal;
    arr[2] = user_input->gear_position;
    arr[3] = user_input->ignition;
    arr[4] = user_input->end_simulation;
}

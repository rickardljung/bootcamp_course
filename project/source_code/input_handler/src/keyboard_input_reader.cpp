#include "keyboard_input_reader.h"
void InputReader::Run(struct mykey *k, std::atomic<bool> *done, uint8_t *arr)
{
    while(true)
    {
        //read user input
        ReadInputs(k, done); 

        //interpret user input
        if(k->read == false)
        {
            InterpretInput(k);  
        }
        //encode into array
        EncodeArray(arr);

        if(k->key == escape)
        {
            done->exchange(true);
            break;
        }
    }
}
void InputReader::ReadInputs(struct mykey *k, std::atomic<bool> *done)
{
        XNextEvent(display, &event);
        /* keyboard events */
        if (event.type == KeyPress)
        {
            //printf( "KeyPress: %x\n", event.xkey.keycode );

            k->key = event.xkey.keycode;
            k->read = false;
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


void InputReader::InterpretInput(struct mykey *k)
{
    
    if(k->key == key_up) //user pressing acc pedal
    {
        acc_value+=10;
        if(acc_value > 100)
        {
            acc_value = 100;
        }
        k->read = true;
    }
    else if(k->key == key_down) //user releasing acc pedal
    {
        acc_value-=10;
        if(acc_value == 246) // -10 = 246 for uint8
        {
            acc_value = 0;
        }
        k->read = true;
    }
    else if(k->key == key_left) //user pressing brake pedal
    {
        brk_value+=20;
        if(brk_value > 100)
        {
            brk_value = 100;
        }
        k->read = true;
    }
    else if(k->key== key_right) //user releasing brake pedal
    {
        brk_value-=20;
        if(brk_value == 236) // -20 = 236 for uint8
        {
            brk_value = 0;
        }
        k->read = true;
    }
    else if(k->key== key_space) //user toggles ignition request
    {
        if(ign_req)
        {
            ign_req = 0;
        }
        
        else
        {
            ign_req = 1;
        }
        k->read = true;
    }
    else if(k->key == key_p)
    {
        gear_pos_req = P;
        k->read = true;
    }
    
    else if(k->key == key_n)
    {
        gear_pos_req = N;
        k->read = true;
    }
    else if(k->key == key_d)
    {
        gear_pos_req = D;
        k->read = true;
    }
    else if(k->key == key_r)
    {
        gear_pos_req = R;
        k->read = true;
    }
    else if(k->key == escape){
        end_sim = 1;
        k->read = true;
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

void InputReader::EncodeArray(uint8_t *arr)
{
    arr[0] = acc_value;
    arr[1] = brk_value;
    arr[2] = gear_pos_req;
    arr[3] = ign_req;
    arr[4] = end_sim;
}

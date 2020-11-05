#include "InputReader.h"

void InputReader::ReadInputs(struct mykey *K){
    
    
    while(true)
    {
        XNextEvent(display, &event);
        /* keyboard events */
        if (event.type == KeyPress)
        {
            //printf( "KeyPress: %x\n", event.xkey.keycode );

            K->key = event.xkey.keycode;
            K->read = false;
            //std::cout<< "key pressed" << *key << std::endl;
        }
        /*else if (event.type == KeyRelease)
        {
            printf( "KeyRelease: %x\n", event.xkey.keycode );
            returnval = event.xkey.keycode;
        }*/
 
        
        
        if(K->key == ESCAPE) //if ESC is pressed
        {
            break;
        }
        

        
    }
}

InputReader::~InputReader(){
    /* close connection to server */
    XAutoRepeatOn(display);
    XCloseDisplay(display);
}
InputReader::InputReader(){
    
 
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


void InputReader::InterpretInput(struct mykey *K){
    
    if(K->key == key_UP) //user pressing acc pedal
    {
        AccValue+=10;
        if(AccValue > 100)
        {
            AccValue = 100;
        }
        K->read = true;
    }
    else if(K->key == key_DOWN) //user releasing acc pedal
    {
        AccValue-=10;
        if(AccValue == 246) // -10 = 246 for uint8
        {
            AccValue = 0;
        }
        K->read = true;
    }
    else if(K->key == key_LEFT) //user pressing brake pedal
    {
        BrkValue+=20;
        if(BrkValue > 100)
        {
            BrkValue = 100;
        }
        K->read = true;
    }
    else if(K->key== key_RIGHT) //user releasing brake pedal
    {
        BrkValue-=20;
        if(BrkValue == 236) // -20 = 236 for uint8
        {
            BrkValue = 0;
        }
        K->read = true;
    }
    else if(K->key== key_SPACE) //user toggles ignition request
    {
        if(IgnReq)
        {
            IgnReq = 0;
        }
        
        else
        {
            IgnReq = 1;
        }
        K->read = true;
    }
    else if(K->key == key_p)
    {
        GearPosReq = P;
        K->read = true;
    }
    
    else if(K->key == key_n)
    {
        GearPosReq = N;
        K->read = true;
    }
    else if(K->key == key_d)
    {
        GearPosReq = D;
        K->read = true;
    }
    else if(K->key == key_r)
    {
        GearPosReq = R;
        K->read = true;
    }
    
    /*std::cout << "AccValue: " << (int)AccValue << std::endl;
    std::cout << "BrkValue: " << (int)BrkValue << std::endl;
    std::cout << "IgnReq: " << (int)IgnReq << std::endl;
    switch (GearPosReq){
        case(P) :   std::cout << "GearPosReq: P" << std::endl;
                    break;
        case(N) :   std::cout << "GearPosReq: N" << std::endl;
                    break;
        case(D) :   std::cout << "GearPosReq: D" << std::endl;
                    break;
        case(R) :   std::cout << "GearPosReq: R" << std::endl;
                    break;
    }*/
}

void InputReader::EncodeArray(uint8_t *arr){
    arr[0] = AccValue;
    arr[1] = BrkValue;
    arr[2] = GearPosReq;
    arr[3] = IgnReq;
}

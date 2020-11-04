#include "socketcan.h"
#include <iostream>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>


void send_input(unsigned int pressed_key){
    //receive user input
    //interpret input, range check
    //decode to CAN payload
    //send on vcan

    scpp::SocketCan socket;
    if (socket.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }

    scpp::CanFrame can_frame;

    can_frame.id = 1;
    can_frame.len = 1;

    can_frame.data[0] = pressed_key;

    auto write_sc_status = socket.write(can_frame);

    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
    else
        printf("Message was written to the socket \n");
}


 
int main()
{
    Display *display;
    Window window;
    XEvent event;
    int s;
 
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
 
    /* event loop */
    while (1)
    {
        XNextEvent(display, &event);
 
        /* keyboard events */
        if (event.type == KeyPress)
        {
            send_input(event.xkey.keycode);
            printf( "KeyPress: %x\n", event.xkey.keycode );

            /* exit on ESC key press */
            if ( event.xkey.keycode == 0x09 )
                break;
        }
        else if (event.type == KeyRelease)
        {
            printf( "KeyRelease: %x\n", event.xkey.keycode );
        }
    }

    /* close connection to server */
    XAutoRepeatOn(display);
    XCloseDisplay(display);
    
 
    return 0;
}
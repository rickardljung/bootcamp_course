#include "vehicle.h"
#include "user_input.h"
#include <iostream>
#include "can_buffer.h"
#include "socketcan.h"
#include "can_io_thread.h"
#include <thread>

int main() {
    bool return_value = 0;
    scpp::SocketCan socket;

    if (socket.Initialize("vcan0"))
    {
        //starts new thread reading can messages and writes to can_buffer
        CanIOThread io_thread(&socket, 1, 2);

        //starts simulation reading from can_buffer in main thread.
        Vehicle vehicle;
        vehicle.Run();
    } else
    {
        return_value = 1;
    }

    return return_value;
}
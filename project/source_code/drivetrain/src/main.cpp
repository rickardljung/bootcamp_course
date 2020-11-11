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
    auto result = socket.open("vcan0");
    if (result!=scpp::STATUS_OK) {
            std::cout << "Nothing to read " << result <<std::endl;
            return 0;
    }

    if (socket.open("vcan0") == scpp::STATUS_OK)
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
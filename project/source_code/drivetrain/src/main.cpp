#include "vehicle.h"
#include "can_io_thread.h"
#include <iostream>

int main() {
    bool return_value = 0;
    scpp::SocketCan socket;

    if (socket.Initialize("vcan0"))
    {
        std::promise<void> promise;
        std::future<void> future = promise.get_future();
        //starts new thread handling input and output on CAN. Uses can_buffer
        CanIOThread io_thread(&socket, &promise, 1, 2);

        Vehicle vehicle;
        //starts simulation, reading and writing to can_buffer
        std::future_status status;
        while (status != std::future_status::ready) {
            status = future.wait_for(std::chrono::milliseconds(3));
            vehicle.Run();
        }
    } else
    {
        return_value = 1;
    }

    return return_value;
}
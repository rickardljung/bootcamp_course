#include "vehicle.h"
#include "can_io_thread.h"
#include <iostream>

int main() {
    bool return_value = 0;

    scpp::SocketCan socket;
    auto result = socket.open("vcan0");

    if (result == scpp::STATUS_OK)
    {
        std::promise<void> promise;
        std::future<void> future = promise.get_future();
        //starts new thread handling input and output on CAN. Uses can_buffer
        CanIOThread io_thread(&socket, &future, 1, 2);

        Vehicle vehicle;
        //starts simulation, reading and writing to can_buffer
        bool simulation_running = true;
        while (simulation_running) {

            vehicle.Run();
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
    } else
    {
        std::cout << "Failed to open socket: " << result <<std::endl;
        return_value = 1;
    }
    return return_value;
}
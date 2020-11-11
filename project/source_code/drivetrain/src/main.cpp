#include "vehicle.h"
#include "can_io_thread.h"

int main() {
    bool return_value = 0;
    scpp::SocketCan socket;

    if (socket.Initialize("vcan0"))
    {
        std::promise<int> promise;
        std::future<int> future = promise.get_future();
        //starts new thread reading can messages and writes to can_buffer
        CanIOThread io_thread(&socket, &promise, 1, 2);

        //starts simulation reading from can_buffer in main thread.
        Vehicle vehicle;

        vehicle.Run();
    } else
    {
        return_value = 1;
    }

    return return_value;
}
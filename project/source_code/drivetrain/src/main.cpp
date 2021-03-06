#include "vehicle.h"
#include "can_buffer.h"
#include "can_io_thread.h"
#include "gearbox_simulator.h"

#include <iostream>

int main(int argc, char *argv[])
{
    bool return_value = 0;

    scpp::SocketCan socket;
    auto result = socket.open(argv[1]);
    if (result != scpp::STATUS_OK)
    {
        std::cout << "Failed to open socket: " << result <<std::endl;
        return 1;
    }

    CanBuffer canbuffer_tx;
    CanBuffer canbuffer_rx;
    std::promise<void> promise;
    std::future<void> future = promise.get_future();
    uint8_t receive_message_id[1] = {1};
    size_t receive_message_id_size = 1;
    //starts new thread handling input and output on CAN. Uses can_buffer
    CanIOThread<CanBuffer> io_thread(&socket, &future, receive_message_id, receive_message_id_size, canbuffer_tx, canbuffer_rx);
    myVolvoXC60 vehicle(canbuffer_tx, canbuffer_rx);

    int i = 0;
    while (vehicle.Run())
    {
        std::this_thread::sleep_for(std::chrono::microseconds(sampletime_micro));
        if (canbuffer_rx.GotNewInput())
        {
            i = 0;

        }
        else if(++i > 100000) // buffer is empty for over 1 second, lost com
        {
            break;
        }
    }
    promise.set_value();

    std::cout << "drivetrain returned with return value: " << return_value << std::endl;
    return return_value;
}

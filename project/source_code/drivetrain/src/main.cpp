#include "vehicle.h"
#include "can_io_thread.h"
#include <iostream>

int main()
{
    bool return_value = 0;

    scpp::SocketCan socket;
    auto result = socket.open("vcan0");
    if (result == scpp::STATUS_OK)
    {
        std::promise<void> promise;
        std::future<void> future = promise.get_future();
        uint8_t receive_message_id[1] = {1};
        size_t receive_message_id_size = 1;
        //starts new thread handling input and output on CAN. Uses can_buffer
        CanIOThread io_thread(&socket, &future, receive_message_id, receive_message_id_size);

        Vehicle vehicle;
        int i = 0;
        bool run_simulation = true;
        while (run_simulation)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(5));
            if (!CanBuffer::GetInstance().ReceiveBufferEmpty())
            {
                i = 0;
                run_simulation = vehicle.Run();
            } else
            {
                if(++i > 100000) // buffer is empty for over 1 second
                {
                    break;
                } else {continue;}
            }
        }
        promise.set_value();
    } else
    {
        std::cout << "Failed to open socket: " << result <<std::endl;
        return_value = 1;
    }
    return return_value;
}
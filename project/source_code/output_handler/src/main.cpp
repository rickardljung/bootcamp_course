#include <thread>
#include "can_io_thread.h"
#include <chrono>
#include <iostream>
#include "socketcan.h"

using namespace scpp;

int main(){

    bool return_value = 0;

    scpp::SocketCan socket;
    auto result = socket.open("vcan0");

    if (result == scpp::STATUS_OK)
    {
        std::promise<void> promise;
        std::future<void> future = promise.get_future();
        uint8_t receive_message_id[2] = {1,2};
        size_t receive_message_id_size = 2; //TODO: replace with siceof??
        //starts new thread handling input and output on CAN. Uses can_buffer
        CanIOThread io_thread(&socket, &future, receive_message_id, receive_message_id_size);

        std::future_status status;
        while (status != std::future_status::ready) {
            std::this_thread::sleep_for(std::chrono::microseconds(5));
            CanData data = CanBuffer::GetInstance().PullRx();
            if (data.id == 1)
            {
                UserInput *input = reinterpret_cast<UserInput*>(data.payload);
                if (input->end_simulation) {
                    break;
                }
            }
            if (data.id == 2)
            {
                std::cout << "EngSts: " << static_cast<int>(received_can_data[0]) << std::endl;
                std::cout << "RPM: " << static_cast<int>(received_can_data[1]*(int)37) << std::endl;
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

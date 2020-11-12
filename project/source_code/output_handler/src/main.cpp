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

    if (result!=scpp::STATUS_OK) {
            std::cout << "Nothing to read " << result <<std::endl;
            return 0;
    }

    if (socket.open("vcan0") == scpp::STATUS_OK)
    {
        std::promise<void> promise;
        std::future<void> future = promise.get_future();
        //starts new thread reading can messages and writes to can_buffer
        CanIOThread io_thread(&socket, &promise, 2, 0);

        std::future_status status;
        while (status != std::future_status::ready) {
            status = future.wait_for(std::chrono::milliseconds(100));
            uint8_t *received_can_data = CanBuffer::GetInstance().PullRx();

            std::cout << "Output Acc: " << static_cast<int>(received_can_data[0]) << std::endl;
        }

    } else
    {
        return_value = 1;
    }

    return return_value;
}

#include "can_io_thread.h"

#include <thread>
#include <chrono>
#include <iostream>

int main(){

    bool return_value = 0;

    scpp::SocketCan socket;
    auto result = socket.open("vcan0");

    if (result == scpp::STATUS_OK)
    {
        CanBuffer canbuffer;
        std::promise<void> promise;
        std::future<void> future = promise.get_future();
        uint8_t receive_message_id[2] = {1,2};
        size_t receive_message_id_size = 2; //TODO: replace with siceof??
        //starts new thread handling input and output on CAN. Uses can_buffer
        CanIOThread<CanBuffer> io_thread(&socket, &future, receive_message_id, receive_message_id_size, canbuffer);

        bool simulation_running = true;
        while (simulation_running) {
            std::this_thread::sleep_for(std::chrono::microseconds(5));

            std::unordered_map<int, CanData> candata_map = canbuffer.Pull();
            for (auto const &element : candata_map)
            {
                CanData can = element.second;
                if (can.id == 1)
                {
                    UserInput *input = reinterpret_cast<UserInput*>(can.payload);
                    std::cout << "=============== ID = 1 ===============" << std::endl;
                    std::cout << "Acc: " << static_cast<int>(input->accelerator_pedal) << std::endl;
                    std::cout << "Brake: " << static_cast<int>(input->brake_pedal * (int)37) << std::endl;
                    std::cout << "---------------------------------" << std::endl;

                    if (input->end_simulation) {
                        simulation_running = false;
                        break;
                    }
                }
                if (can.id == 2)
                {
                    std::cout << "=============== ID = 2 ===============" << std::endl;
                    std::cout << "EngSts: " << static_cast<int>(can.payload[0]) << std::endl;
                    std::cout << "RPM: " << static_cast<int>(can.payload[1] * (int)37) << std::endl;
                    std::cout << "---------------------------------" << std::endl;
                }
            }
        }
        promise.set_value();
    } else
    {
        std::cout << "Failed to open socket: " << result <<std::endl;
        return_value = 1;
    }
    std::cout << "output_handler returned with return value: " << return_value << std::endl;
    return return_value;
}

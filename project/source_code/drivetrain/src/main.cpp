#include "vehicle.h"
#include "can_io_thread.h"
#include <iostream>


const float final_gear = 3.42;
const float weight = 1000;
const float tire_diameter = 0.680;

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

        Engine engine(1000, 9000);
        double gear_ratios[] = {3.00, 3.18, 2.26, 1.68, 1.29, 1.06, 0.88};
        Gearbox gearbox(gear_ratios, 7);
        Vehicle vehicle(&gearbox, &engine, final_gear, weight, tire_diameter);
        int i = 0;
        while (vehicle.Run())
        {
            std::this_thread::sleep_for(std::chrono::microseconds(sampletime_micro));
            if (!CanBuffer::GetInstance().ReceiveBufferEmpty())
            {
                i = 0;

            } else
            {
                if(++i > 100000) // buffer is empty for over 1 second, lost com
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
    std::cout << "drivetrain returned with return value: " << return_value << std::endl;
    return return_value;
}
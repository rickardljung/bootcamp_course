#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <future>
#include <iostream>
#include <cstring>
#include "user_input.h"
#include "keyboard_input_reader.h"
#include "socketcan.h"


int main(){
    int returnval = 0;
    //initiate vcan0
    scpp::SocketCan socket;
    auto result = socket.open("vcan0");
    if(result != scpp::STATUS_OK){
        std::cout << "Failed to open socket: " << result <<std::endl;
        returnval = 1;
    }
    else
    {
        //mutex for locking user_input
        std::mutex user_input_mtx;

        //struct containing user input values
        UserInput user_input;
        std::memset(&user_input,0,sizeof(UserInput));

        std::promise<void> promise;
        std::future<void> future = promise.get_future();

        //create a thread for running the InputReader
        std::thread read_inputs(
        [&user_input, &user_input_mtx, &promise](){
            //initiate key board reading
            InputReader input_reader;
            //run input_reader
            while(input_reader.Run(&user_input, &user_input_mtx));
            //inform main thread that this thread is finished
            promise.set_value();
        }
        );
        std::future_status status;

        uint8_t payload[msg_len];
        std::memset(payload,0,msg_len);
        while(status != std::future_status::ready)
        {
            status = future.wait_for(std::chrono::milliseconds(10));
            //send CAN-message
            EncodePayload(payload, &user_input_mtx, &user_input);
            socket.write(payload, msg_id, msg_len);
        }
    read_inputs.join();
    }
    return returnval;
}
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <future>
#include <iostream>
#include <cstring>
#include "keyboard_input_reader.h"
#include "can_io_thread.h"
#include "can_buffer.h"

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
    
    std::promise<void> promise;
    std::future<void> future = promise.get_future();

    //initiate keyboard reading
    InputReader input_reader;

    //spawn a thread transmitting CAN messages
    CanIOThread io_thread(&socket, &future, 0, 0);
    
    while(input_reader.Run());

    //make sure end simulation is sent in CAN frame before exiting
    future.wait_for(std::chrono::milliseconds(1));
    promise.set_value();
    }
    std::cout << "input_handler returned with return value: " << returnval << std::endl;
    return returnval;
}

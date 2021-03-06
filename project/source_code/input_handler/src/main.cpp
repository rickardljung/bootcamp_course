#include "can_buffer.h"
#include "can_io_thread.h"
#include "keyboard_input_reader.h"

#include <mutex>
#include <thread>
#include <chrono>
#include <future>
#include <cstring>
#include <iostream>


int main(int argc, char *argv[]){
    int returnval = 0;
    //initiate vcan0
    scpp::SocketCan socket;
    auto result = socket.open(argv[1]);
    if(result != scpp::STATUS_OK){
        std::cout << "Failed to open socket: " << result <<std::endl;
        returnval = 1;
    }
    else
    {
        CanBuffer canbuffer, canbuffer_dummy;
        std::promise<void> promise;
        std::future<void> future = promise.get_future();

        //initiateCanBuffer keyboard reading
        InputReader<CanBuffer> input_reader(canbuffer);

        //spawn a thread transmitting CAN messages
        CanIOThread<CanBuffer> io_thread(&socket, &future, nullptr, 0, canbuffer, canbuffer_dummy);

        while(input_reader.Run());

        //make sure end simulation is sent in CAN frame before exiting
        future.wait_for(std::chrono::milliseconds(1));
        promise.set_value();
    }
    std::cout << "input_handler returned with return value: " << returnval << std::endl;
    return returnval;
}

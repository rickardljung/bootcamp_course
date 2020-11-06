#include "keyboard_input_reader.h"
#include "socketcan.h"
#include <thread>
#include <chrono>


int main(){
    int returnval = 0;

    //initiate key board reading
    InputReader input_reader;

    //initiate vcan0
    scpp::SocketCan socket;
    if(!socket.Initialize("vcan0")){
        returnval = 1;
    }

    //payload to be sent in canframe
    uint8_t payload[msg_len];
    
    //create a thread for running the InputReader
    std::thread t1(
    [&](){
            //run input_reader
            input_reader.Run(payload);
    }
    );    
    while(true)
    {
        //send CAN-message
        socket.write(payload, msg_id, msg_len);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        if(!input_reader.is_running)
        {
            break;
        }
        
    }
    std::cout << "1" << std::endl << std::flush;
    t1.join();
    std::cout << "2" << std::endl << std::flush;
    return returnval;
}
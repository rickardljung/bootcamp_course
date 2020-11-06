#include "keyboard_input_reader.h"
#include "socketcan.h"
#include <thread>
#include <chrono>


int main(){

    //initiate key board reading
    InputReader input_reader;

    //initiate vcan0
    scpp::SocketCan socket("vcan0");

    //payload to be sent in canframe
    uint8_t payload[msg_len];
    
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
        
        if(!input_reader.is_running)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    t1.join();
    return 0;
}
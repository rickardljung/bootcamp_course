#include "can_fr_handler.h"
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
    
    //struct containing user input values
    UserInput user_input;

    //create a thread for running the InputReader
    std::thread t1(
    [&](){
            //run input_reader
            input_reader.Run(&user_input);
    }
    );    
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        //send CAN-message
        EncodePayload(payload, &user_input);
        socket.write(payload, msg_id, msg_len);
        if(!input_reader.is_running)
        {
            break;
        }
    }
    
    t1.join();
    return returnval;
}
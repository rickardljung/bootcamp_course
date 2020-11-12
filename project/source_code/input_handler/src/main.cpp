#include "user_input.h"
#include "keyboard_input_reader.h"
#include "socketcan.h"
#include <thread>
#include <chrono>
#include <mutex>


int main(){
    int returnval = 0;

    //initiate key board reading
    InputReader input_reader;

    //mutex for locking user_input
    std::mutex user_input_mtx;

    //initiate vcan0
    scpp::SocketCan socket;
    if(socket.open("vcan0") != scpp::STATUS_OK){
        returnval = 1;
    }
    else
    {
        //payload to be sent in canframe
        uint8_t payload[msg_len];

        //struct containing user input values
        UserInput user_input;

        //create a thread for running the InputReader
        std::thread read_inputs(
        [&user_input, &input_reader, &user_input_mtx](){
                //run input_reader
                while(true)
                {
                    if(!input_reader.Run(&user_input, &user_input_mtx))
                    {
                        break;
                    }
                }
        }
        );
        while(true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            //send CAN-message
            {
                std::lock_guard<std::mutex> lock (user_input_mtx);
                EncodePayload(payload, &user_input);
            }
            socket.write(payload, msg_id, msg_len);
            
            if(payload[4]) //end_simulation == 1
            {
                break;
            }
        }

    read_inputs.join();
    }



    return returnval;
}
#include "InputReader.h"
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

    //storage for keyboard input
    struct mykey the_key;

    //to know if thread 1 is finished
    std::atomic<bool> t1_done;
    t1_done.exchange(false);

    
    std::thread t1(
    [&](){
        while(true){
            //get input from user
            input_reader.ReadInputs(&the_key, &t1_done); 

            //interpret user input
            if(the_key.read == false)
            {
                input_reader.InterpretInput(&the_key);  
            }
            //encode into array
            input_reader.EncodeArray(payload);

            //if ESC is pressed exit the loop
            if(the_key.key == ESCAPE)
            {
                t1_done.exchange(true);
                break;
            }
        }
    }
    );

    while(true){
        //send array to CANWRITER
        socket.write(payload, msg_id, msg_len);

        //if thread 1 finished, break
        bool b1, b2=true;
        if(t1_done.compare_exchange_strong(b2,b1))
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    t1.join();
    return 0;
}
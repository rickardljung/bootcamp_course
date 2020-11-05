#include "InputReader.h"
#include "CANWriter.h"
#include <thread>
const uint8_t msg_id = 1;
const uint8_t msg_len = 4;


int main(){
    //initiate key board reading
    InputReader IR;
    scpp::SocketCan socket("vcan0");
    //scpp::CanFrame can_frame;
    uint8_t Payload[4] = {0, 0, 0, 0};
    struct mykey K;

  
    std::thread t1(
    [&](){
        IR.ReadInputs(&K);
    }
    );
    while(1){
        //get input from user   - DONE
        //interpret user input  - DONE

        //encode into array     - DONE
        
        //send array to CANWRITER - DONE

        //key = IR.ReadInputs();
        if(K.read == False)
        {
            IR.InterpretInput(&K);
        }
        //IR.InterpretInput(IR.ReadInputs());
       
        
        IR.EncodeArray(Payload);
        socket.write(Payload, msg_id, msg_len);
        //send_input(Payload);
        /*for(int i=0; i<4; i++)
        {
            std::cout << "Payload [" << i << "]: " << (int)Payload[i] << std::endl;
        }*/
        //delay ??s

        if(K.key == ESCAPE)
        {
            break;
        }
    }
    t1.join();    
    return 0;
}
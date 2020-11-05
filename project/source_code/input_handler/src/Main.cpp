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
    uint8_t key;
    std::thread t1(IR.ReadInputs());
    while(1){
        //get input from user   - DONE
        //interpret user input  - DONE

        //encode into array     - DONE
        
        //send array to CANWRITER - DONE

        //key = IR.ReadInputs();
       // IR.InterpretInput(key);
        //IR.InterpretInput(IR.ReadInputs());
       
        
        IR.EncodeArray(Payload);
        socket.write(Payload, msg_id, msg_len);
        //send_input(Payload);
        for(int i=0; i<4; i++)
        {
            std::cout << "Payload [" << i << "]: " << (int)Payload[i] << std::endl;
        }
        //delay ??
    }

    return 0;
}
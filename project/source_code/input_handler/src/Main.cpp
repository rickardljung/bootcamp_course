#include "InputReader.h"
#include "CANWriter.h"

int main(){
    //initiate key board reading
    InputReader IR;
    uint8_t Payload[4] = {0, 0, 0, 0};
    uint8_t key;
    while(1){
        //get input from user   - DONE
        //interpret user input  - DONE

        //encode into array     - DONE

        //send array to CANWRITER - DONE

        key = IR.ReadInputs();
        IR.InterpretInput(key);
        //IR.InterpretInput(IR.ReadInputs());
        if(key == ESCAPE) //if ESC is pressed
        {
            break;
        }
        IR.EncodeArray(Payload);
        send_input(Payload);
        /*for(int i=0; i<4; i++)
        {
            std::cout << "Payload [" << i << "]: " << (int)Payload[i] << std::endl;
        }*/
        //delay ??
    }
    return 0;
}
#include "CANWriter.h"
void initialise_CAN(scpp::SocketCan &socket, scpp::CanFrame &can_frame)
{
    if (socket.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }
        can_frame.id = 1;
        can_frame.len = 4;


}
void send_input(uint8_t *payload){
    //receive user input
    //interpret input, range check
    //decode to CAN payload
    //send on vcan
 


    


    for(int i=0; i<can_frame.len; i++)
    {
        can_frame.data[i] = payload[i];
    }    

    auto write_sc_status = socket.write(can_frame);

    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
    else
        printf("Message was written to the socket \n");

    /*std::cout << "CAN frame: " << (int)can_frame.id << std::endl;
    std::cout << "CAN length: " << (int)can_frame.len << std::endl;
    std::cout << "CAN Data: ";
    for(int j=0; j<can_frame.len; j++)
    {
        std::cout << " " << (int)can_frame.data[j];
    }*/
}
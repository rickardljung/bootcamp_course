#include "socketcan.h"
#include <iostream>

int main() {
    //receive user input
    //interpret input, range check
    //decode to CAN payload
    //send on vcan

    scpp::SocketCan socket;
    if (socket.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }

    scpp::CanFrame can_frame;

    can_frame.id = 1;
    can_frame.len = 1;

    can_frame.data[0] = 100;

    auto write_sc_status = socket.write(can_frame);

    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
    else
        printf("Message was written to the socket \n");

    return 0;


}
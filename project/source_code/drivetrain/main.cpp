//#include "vehicle.hpp"
#include "user_input.hpp"
// #include "can_reader.hpp"
// #include "ringbuffer.hpp"
#include <iostream>
#include "can_buffer.hpp"
#include "socketcan.h"
#include <thread>

int main() {

    scpp::SocketCan sockat_can;
    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }
    while (true) {
        scpp::CanFrame fr;
        if (sockat_can.read(fr) == scpp::STATUS_OK) {    
            
            user_input_struct user_input, user_input_2;
            user_input.acc = fr.data[0];
            user_input.brk = fr.data[1];
            user_input.gear = fr.data[2];
            user_input.ignition = fr.data[3];

            CanBuffer::getInstance().add(&user_input); 

            user_input_2 = CanBuffer::getInstance().pull();

            std::cout << "Acc ped pos: " << static_cast<int> (user_input_2.acc) << std::endl;      

        } else {
            for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
        }
    }



    //Ringbuffer<user_input, 50> buffer;
    //CanReader reader(&buffer); //thread which will write to buffer

    /*
    Vehicle v(&buffer);

    v.run();

    delete input;

    */
}
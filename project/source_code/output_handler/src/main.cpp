#include <thread>
#include "can_reader.h"
#include <chrono>
#include <iostream>
#include "socketcan.h"

using namespace scpp;

int main(){


    bool return_value = 0;

    scpp::SocketCan socket;
    auto result = socket.open("vcan0");
    
    if (result!=scpp::STATUS_OK) {
            std::cout << "Nothing to read " << result <<std::endl;
            return 0;
    }

    if (socket.open("vcan0") == scpp::STATUS_OK)
    {
        //starts new thread reading can messages and writes to can_buffer
        CanReader reader(&socket, 2);
        while(1)
        {
            uint8_t *received_can_data = CanBuffer::GetInstance().Pull();

            std::cout << "Output Acc: " << static_cast<int>(received_can_data[0]) << std::endl;
        }

    } else
    {
        return_value = 1;
    }

    return return_value;


//    if (!result) {
//            std::cout << "cannot open " << result <<std::endl;
//            return 0;
//    }

    // size_t i=0;

    // while (1)
    // {
        
    //     CanFrame fr;
    //     SocketCanStatus result2  = socket.read(fr);

    //     if (result2 == STATUS_NOTHING_TO_READ)
    //     {
    //         std::cout << "Nothing to read " << i << std::endl;
    //         if(++i>2000)break;
    //         else   continue;

    //     } else if (result2 != STATUS_OK) {
    //         std::cout << "Error " << result2<<std::endl;
    //         /*if(++i>2)*/{break;}
    //     }
    //     else i =0;
    //     std::cout << "Receiving stuff" << fr.data[0]<< fr.data[1]<< fr.data[2]<< fr.data[3]<< std::endl;
    //     std::this_thread::sleep_for (std::chrono::milliseconds(1));
    // }
    // return 1;

}

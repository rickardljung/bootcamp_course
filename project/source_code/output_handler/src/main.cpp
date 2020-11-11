#include "socketcan.h"
#include <thread>
#include <chrono>
#include <iostream>


int main(){
    bool return_value = 0;
    
    SocketCan socket;
    /*bool result = */socket.open("vcan0");
    
//    if (!result) {
//            std::cout << "cannot open " << result <<std::endl;
//            return 0;
//    }

    size_t i=0;

    while (1)
    {
        
        CanFrame fr;
        SocketCanStatus result2  = socket.read(fr);

        if (result2 == STATUS_NOTHING_2_READ)
        {
            std::cout << "Nothing to read " << std::endl;
            continue;

        } else if (result2 != STATUS_OK) {
            std::cout << "Error " << result2<<std::endl;
            /*if(++i>2)*/{break;}
        }
        else i =0;
        std::cout << "Receiving stuff" << fr.data[0]<< fr.data[1]<< fr.data[2]<< fr.data[3]<< std::endl;
        std::this_thread::sleep_for (std::chrono::nanoseconds(10));
    }
    return 1;

}

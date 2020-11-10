#include "can_reader.h"
#include "socketcan.h"
#include <thread>
#include <chrono>
#include <iostream>


int main(){
    bool return_value = 0;
    
    scpp::SocketCan socket;
    auto result = socket.Initialize("vcan0");
    
    if (result!=scpp::STATUS_OK) {
            std::cout << "cannot open " << result <<std::endl;
            return 0;
    }

    size_t i=0;

    while (1)
    {
        
        scpp::CanFrame fr;
        auto result2  = socket.read(fr);
        if (result2 == scpp::STATUS_OK) {            
            fr.id = 3;
        //       socket.write(fr);
            
            std::cout << "Receiving stuff" << fr.data[0]<< fr.data[1]<< fr.data[2]<< fr.data[3]<< std::endl;
        } 
        else if (result2 == scpp::STATUS_NOTHING_TO_READ)
        {
            std::cout << "Nothing to read " << std::endl;
            if(++i>2){break;}
        }
        else{
            std::cout << ">> Error " << result2 <<std::endl; break;}
    }
    return 1;

    if (socket.Initialize("vcan0"))
    {
        //starts new thread reading can messages and writes to can_buffer
        CanReader reader(&socket, 2);
        while(1)
        {
            uint8_t *received_can_data = CanBuffer::GetInstance().Pull();
            
        //    std::cout << "Received Acc: " << static_cast<int>(received_can_data[0]) << std::endl;
        //    std::cout << "Received Brake: " << static_cast<int>(received_can_data[1]) << std::endl;

            //if(received_can_data[0])break;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

    } 
    else
    {
        return_value = 1;
    }


    return 0;
}
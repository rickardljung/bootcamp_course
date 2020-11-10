#include "vehicle.h"
#include "user_input.h"
#include <iostream>
#include "can_buffer.h"
#include "socketcan.h"
#include "can_reader.h"
#include <thread>

int main() {
    bool return_value = 0;

    scpp::SocketCan socket;
    auto result = socket.Initialize("vcan0");
    if (result!=scpp::STATUS_OK) {
            std::cout << "Nothing to read " << result <<std::endl;
            return 0;
    }

    size_t i=0;

    while (1)
    {
        
        scpp::CanFrame fr;
        result  = socket.read(fr);
        if ((result == scpp::STATUS_OK)) {            
            fr.id = 3;
            socket.write(fr);
            std::cout << "Nothing to read1 " << std::endl;
        } 
        else if (result == scpp::STATUS_NOTHING_TO_READ)
        {
            std::cout << "Nothing to read2 " << std::endl;
            if(++i>2){break;}
        }
        else{
            std::cout << "Nothing to read " << result <<std::endl; break;}
    }
    
    return 1;

    if (socket.Initialize("vcan0"))
    {
        //starts new thread reading can messages and writes to can_buffer
        CanReader reader(&socket, 1);

        //starts simulation reading from can_buffer in main thread. Creates thread writing ouput "socket"
        Vehicle vehicle(&socket);
    } else
    {
        return_value = 1;
    }

    return return_value;
}
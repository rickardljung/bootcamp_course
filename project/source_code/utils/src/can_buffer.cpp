//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include "user_input.h"
#include "can_buffer.h"
#include <iostream>
#include <cstring>


void CanBuffer::Add(uint8_t data[]) {  //this will be replaced by ringbuffer
    
    if(data!=nullptr)
    {
        std::memcpy(this->received_can_data, data, sizeof(&data));  
    }
    else
    {
        exit(-1);
    } 
}


uint8_t * CanBuffer::Pull() {            //this will be replaced by ringbuffer
    return this->received_can_data;
}
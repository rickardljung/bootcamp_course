//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include "user_input.h"
#include "can_buffer.h"

void CanBuffer::Add(uint8_t data[]) {  //this will be replaced by ringbuffer
    *this->received_can_data = *data;
}

uint8_t * CanBuffer::Pull() {            //this will be replaced by ringbuffer
    return this->received_can_data;
}
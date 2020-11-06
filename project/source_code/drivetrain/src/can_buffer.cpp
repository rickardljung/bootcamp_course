//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include "user_input.h"
#include "can_buffer.h"

void CanBuffer::Add(UserInput *input) {  //this will be replaced by ringbuffer
    received_can_data = *input;
}

user_input_struct CanBuffer::Pull() {            //this will be replaced by ringbuffer
    return this->received_can_data;
}
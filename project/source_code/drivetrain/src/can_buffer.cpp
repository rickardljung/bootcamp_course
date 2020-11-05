//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include "user_input.hpp"
#include "can_buffer.hpp"

void CanBuffer::add(user_input_struct *input) {  //this will be replaced by ringbuffer
    received_can_data = *input;
}

user_input_struct CanBuffer::pull() {            //this will be replaced by ringbuffer
    return this->received_can_data;
}
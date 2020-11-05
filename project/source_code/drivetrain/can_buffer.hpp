//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#ifndef CAN_BUFFER_H
#define CAN_BUFFER_H
#include "user_input.hpp"

class CanBuffer
{
    public:
        static CanBuffer& getInstance(){
            static CanBuffer    instance;
            return instance;
        }
        void add(user_input_struct *input);
        user_input_struct pull();

        CanBuffer(CanBuffer const&)       = delete;
        void operator=(CanBuffer const&)  = delete;
    private:
        CanBuffer() {};
        user_input_struct received_can_data; //this will be replaced by ringbuffer
};

#endif
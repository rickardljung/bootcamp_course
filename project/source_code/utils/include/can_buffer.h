//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#ifndef CAN_BUFFER_H
#define CAN_BUFFER_H
#include "user_input.h"

class CanBuffer
{
    public:
        static CanBuffer& GetInstance(){
            static CanBuffer    instance;
            return instance;
        }
        void Add(uint8_t data[]);
        uint8_t * Pull();

        CanBuffer(CanBuffer const&)       = delete;
        void operator=(CanBuffer const&)  = delete;
    private:
        CanBuffer() {};
        //UserInput received_can_data; //this will be replaced by ringbuffer
        uint8_t received_can_data[8];
};

#endif
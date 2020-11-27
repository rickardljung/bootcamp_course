//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#ifndef CAN_BUFFER_H
#define CAN_BUFFER_H
#include "user_input.h"

typedef struct CanData_struct{
    uint32_t id = 0;
    uint8_t payload[8] = {0,0,0,0,0,0,0,0};
    uint8_t length = 0;
} CanData;

class CanBuffer
{
    public:
        static CanBuffer& GetInstance(){
            static CanBuffer    instance;
            return instance;
        }
        CanBuffer(CanBuffer const&)       = delete;
        void operator=(CanBuffer const&)  = delete;
        void AddTx(const uint32_t *id, uint8_t payload[], const uint8_t *length);
        void AddRx(const uint32_t *id, uint8_t payload[], const uint8_t *length);
        CanData PullTx();
        CanData PullRx();
        bool ReceiveBufferEmpty();
        //bool TransmitBufferEmpty();
    private:
        CanBuffer() {};
        //UserInput received_CanData; //this will be replaced by ringbuffer
        CanData receive_candata;
        CanData transmit_candata;
        bool receive_empty = true;
        bool transmit_empty = true;
        std::mutex receive_buffer_mutex;
        std::mutex transmit_buffer_mutex;
};

#endif
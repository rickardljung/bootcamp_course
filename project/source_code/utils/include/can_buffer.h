//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#ifndef CAN_BUFFER_H
#define CAN_BUFFER_H
#include "user_input.h"

const int NBR_TX_FRAMES = 2;

typedef struct CanData_struct{
    uint32_t id = 0;
    uint8_t payload[8] = {0,0,0,0,0,0,0,0};
    uint8_t length = 0;
} CanData;

template <int frames_to_send>
class CanBuffer
{
    public:
        //constexpr uint8_t x = frames_to_send;

        // static CanBuffer& GetInstance(){
        //     static CanBuffer    instance;
        //     return instance;
        // }
        // CanBuffer(CanBuffer const&)       = delete;
        // void operator=(CanBuffer const&)  = delete;
        CanBuffer()=default;
        void AddTx(const uint32_t *id, uint8_t payload[], const uint8_t *length);
        void AddRx(const uint32_t *id, uint8_t payload[], const uint8_t *length);
        CanData PullTx();
        CanData PullRx();
        bool ReceiveBufferEmpty();
        bool TransmitBufferEmpty();
    private:
        //UserInput received_CanData; //this will be replaced by ringbuffer
        CanData receive_candata[frames_to_send];
        CanData transmit_candata[frames_to_send];
        bool receive_empty = true;
        bool transmit_empty = true;
        std::mutex receive_buffer_mutex;
        std::mutex transmit_buffer_mutex;
};
/*!
* Check if receive buffer contains any elements
* @return TRUE if receive buffer is empty
*/
template <int frames_to_send>
inline bool CanBuffer<frames_to_send>::ReceiveBufferEmpty()
{
    return this->receive_empty;
}
/*!
* Check if transmit buffer contains any elements
* @return TRUE if transmit buffer is empty
*/
template <int frames_to_send>
inline bool CanBuffer<frames_to_send>::TransmitBufferEmpty()
{
    return this->transmit_empty;
}
#endif
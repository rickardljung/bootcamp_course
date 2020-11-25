//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#ifndef CAN_BUFFER_H
#define CAN_BUFFER_H
#include "can_buffer.h"
#include "user_input.h"

#include <thread>
#include <cstring>
#include <iostream>
#include <unordered_map>


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
        // void AddTx(const uint32_t *id, uint8_t payload[], const uint8_t *length);
        // void AddRx(const uint32_t *id, uint8_t payload[], const uint8_t *length);
        // CanData PullTx();
        // CanData PullRx();

        void AddTx(const uint32_t *id, uint8_t payload[], const uint8_t *length);
        CanData PullTx();

        // bool ReceiveBufferEmpty();
        // bool TransmitBufferEmpty();
    private:
        //UserInput received_CanData; //this will be replaced by ringbuffer
        // CanData receive_candata[frames_to_send];
        // CanData transmit_candata[frames_to_send];
       
        std::unordered_map<int, CanData> candata;
        std::mutex transmit_buffer_mutex;
        
        // bool receive_empty = true;
        // bool transmit_empty = true;
        // std::mutex receive_buffer_mutex;
        // std::mutex transmit_buffer_mutex;
};
// /*!
// * Check if receive buffer contains any elements
// * @return TRUE if receive buffer is empty
// */
// template <int frames_to_send>
// inline bool CanBuffer<frames_to_send>::ReceiveBufferEmpty()
// {
//     return this->receive_empty;
// }
// /*!
// * Check if transmit buffer contains any elements
// * @return TRUE if transmit buffer is empty
// */
// template <int frames_to_send>
// inline bool CanBuffer<frames_to_send>::TransmitBufferEmpty()
// {
//     return this->transmit_empty;
// }

// /*!* Adds received can data to the receive (RX) buffer
// * @param data received can data
// */
// template <int frames_to_send>
// void CanBuffer<frames_to_send>::AddRx(const uint32_t *id, uint8_t payload[], const uint8_t *length)
// {
//     for()
//     std::lock_guard<std::mutex> lock(receive_buffer_mutex);
//     std::memcpy(this->receive_candata[frames_to_send].payload, payload, *length);
//     this->receive_candata[frames_to_send].id = *id;
//     this->receive_candata[frames_to_send].length = *length;
//     this->receive_empty = false;
// }
/*!
* Adds data to be sent to the transmit (TX) buffer
* @param data data to be transmitted
*/
template <int frames_to_send>
void CanBuffer<frames_to_send>::AddTx(const uint32_t *id, uint8_t payload[],const uint8_t *length)
{
    std::lock_guard<std::mutex> lock(transmit_buffer_mutex);
    std::memcpy(this->transmit_candata[frames_to_send].payload, payload, *length);
    this->transmit_candata[frames_to_send].id = *id;
    this->transmit_candatap[frames_to_send].length = *length;
    this->transmit_empty = false;
}
/*!
* Pulls next data package from the receive (RX) buffer
* @return received data
*/
template <int frames_to_send>
CanData CanBuffer<frames_to_send>::PullRx()
{
    std::lock_guard<std::mutex> lock(receive_buffer_mutex);
    this->receive_empty = true;
    return this->receive_candata;
}
/*!
* Pulls next data package from the transmit (TX) buffer
* @return data to be transmitted
*/
template <int frames_to_send>
CanData CanBuffer<frames_to_send>::PullTx()
{
    std::lock_guard<std::mutex> lock(transmit_buffer_mutex);
    this->transmit_empty = true;
    return this->transmit_candata;
}

#endif
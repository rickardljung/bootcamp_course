//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include <thread>
#include <cstring>
#include <iostream>
#include "user_input.h"
#include "can_buffer.h"

/*!* Adds received can data to the receive (RX) buffer
* @param data received can data
*/
template <int frames_to_send>
void CanBuffer<frames_to_send>::AddRx(const uint32_t *id, uint8_t payload[], const uint8_t *length)
{
    std::lock_guard<std::mutex> lock(receive_buffer_mutex);
    std::memcpy(this->receive_candata.payload, payload, *length);
    this->receive_candata.id = *id;
    this->receive_candata.length = *length;
    this->receive_empty = false;
}
/*!
* Adds data to be sent to the transmit (TX) buffer
* @param data data to be transmitted
*/
template <int frames_to_send>
void CanBuffer<frames_to_send>::AddTx(const uint32_t *id, uint8_t payload[],const uint8_t *length)
{
    std::lock_guard<std::mutex> lock(transmit_buffer_mutex);
    std::memcpy(this->transmit_candata.payload, payload, *length);
    this->transmit_candata.id = *id;
    this->transmit_candata.length = *length;
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

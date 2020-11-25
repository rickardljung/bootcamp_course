//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include <thread>
#include <cstring>
#include <iostream>
#include "user_input.h"
#include "can_buffer.h"

//Moved to .h 


/*!
* Adds data to be sent to the transmit (TX) buffer
* @param data data to be transmitted
*/

void CanBuffer::Add(const uint32_t& id, uint8_t payload[],const uint8_t& length)
{
    std::lock_guard<std::mutex> lock(transmit_buffer_mutex);
    std::memcpy(this->candata.payload, payload, length);
    this->candata.id = id;
    this->candatap.length = length;
}

/*!
* Pulls next data package from the transmit (TX) buffer
* @return data to be transmitted
*/

CanData CanBuffer::Pull(uint32_t& frames_to_send)
{
    std::lock_guard<std::mutex> lock(transmit_buffer_mutex);
}
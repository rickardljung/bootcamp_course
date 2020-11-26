//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include <thread>
#include <cstring>
#include <iostream>
#include "user_input.h"
#include "can_buffer.h"

/*!
* Adds data to be sent to the transmit (TX) buffer
* @param data data to be transmitted
*/
void CanBuffer::Add(const uint32_t& id, uint8_t payload[],const uint8_t& length)
{
    std::lock_guard<std::mutex> lock(buffer_mutex);
    CanData data;
    data.id = id;
    data.length = length;
    memcpy(data.payload,payload,length);
    candata[id] = data;
}

/*!
* Pulls next data package from the transmit (TX) buffer
* @return data to be transmitted
*/
std::unordered_map<int, CanData> CanBuffer::Pull()
{
    std::lock_guard<std::mutex> lock(buffer_mutex);
    return candata;
}
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
    CanData data; 
    data.id = id;
    data.length = length;
    memcpy(data.payload,payload,length);
    {
        std::lock_guard<std::mutex> lock(buffer_mutex);
        candata[id] = std::move(data);
    }
    gotnewinput = 1;
}

/*!
* Pulls next data package from the transmit (TX) buffer
* @return data to be transmitted
*/
std::unordered_map<int, CanData> CanBuffer::Pull()
{
    std::lock_guard<std::mutex> lock(buffer_mutex);
    gotnewinput = 0;
    return candata;
}

/*!
* Gives feedback about incoming new data from CAN, used in vehicle
* to detect lost communication and terminate thread
* @return new data is received
*/
bool CanBuffer::GotNewInput(void)
{
    return gotnewinput;
}
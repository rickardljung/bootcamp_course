//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include "user_input.h"
#include "can_buffer.h"
#include <iostream>
#include <cstring>

/*!
* Adds received can data to the receive (RX) buffer
* @param data received can data
*/
void CanBuffer::AddRx(uint8_t data[]) {  //this will be replaced by ringbuffer

    if(data!=nullptr)
    {
        std::memcpy(this->receive_can_data, data, sizeof(&data));
    }
    else
    {
        exit(-1);
    }
}
/*!
* Adds data to be sent to the transmission (TX) buffer
* @param data data to be transmitted
*/
void CanBuffer::AddTx(uint8_t data[]) {  //this will be replaced by ringbuffer

    if(data!=nullptr)
    {
        std::memcpy(this->transmit_can_data, data, sizeof(&data));
    }
    else
    {
        exit(-1);
    }
}

/*!
* Pulls next data package from the receive (RX) buffer
* @return received data
*/
uint8_t * CanBuffer::PullRx() {            //this will be replaced by ringbuffer
    return this->receive_can_data;
}

/*!
* Pulls next data package from the transmit (TX) buffer
* @return data to be transmitted
*/
uint8_t * CanBuffer::PullTx() {            //this will be replaced by ringbuffer
    return this->transmit_can_data;
}
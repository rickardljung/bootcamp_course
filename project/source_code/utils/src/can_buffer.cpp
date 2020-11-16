//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#include "user_input.h"
#include "can_buffer.h"
#include <iostream>
#include <cstring>

/*!
* Adds received can data to the receive (RX) buffer
* @param data received can data
*/
void CanBuffer::AddRx(const uint32_t *id, uint8_t payload[], const uint8_t *length)
{
    std::memcpy(this->receive_candata.payload, payload, sizeof(&payload));
    this->receive_candata.id = *id;
    this->receive_candata.length = *length;
    this->receive_empty = false;
}
/*!
* Adds data to be sent to the transmit (TX) buffer
* @param data data to be transmitted
*/
void CanBuffer::AddTx(const uint32_t *id, uint8_t payload[],const uint8_t *length)
{
    std::memcpy(this->transmit_candata.payload, payload, sizeof(&payload));
    this->transmit_candata.id = *id;
    this->transmit_candata.length = *length;
    this->transmit_empty = false;
/*!
* Pulls next data package from the receive (RX) buffer
* @return received data
*/
}
CanData CanBuffer::PullRx()
{
    this->receive_empty = true;
    return this->receive_candata;
}
/*!
* Pulls next data package from the transmit (TX) buffer
* @return data to be transmitted
*/
CanData CanBuffer::PullTx()
{
    this->transmit_empty = true;
    return this->transmit_candata;
}
/*!
* Check if receive buffer contains any elements
* @return TRUE if receive buffer is empty
*/
bool CanBuffer::ReceiveBufferEmpty()
{
    return this->receive_empty;
}

/*!
* Check if transmit buffer contains any elements
* @return TRUE if transmit buffer is empty
*/
bool CanBuffer::TransmitBufferEmpty()
{
    return this->transmit_empty;
}
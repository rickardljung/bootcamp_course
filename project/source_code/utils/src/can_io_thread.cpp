#include "can_io_thread.h"
#include <iostream>
#include "user_input.h"

/*!
* Constructor of CanIOThread. Assigns the class members and starts a thread on the function "Run"
* @param socket used for read and write data to can
* @param receive_message_id id of the messages to read
* @param transmit_message_id id of the messages to transmit. 0 if nothing to transmit
*/
CanIOThread::CanIOThread(scpp::SocketCan *socket, std::future<void> *future, uint8_t *receive_message_id, size_t receive_message_id_size) { //TODO break lines
    this->socket = socket;
    this->thread = std::thread(&CanIOThread::Run, this, future, receive_message_id, receive_message_id_size);
}

/*!
* Reads data from CAN and writes it to the receive buffer. Pulls data from the transmit buffer and transmits it to can.
* Loops until a "end simulation" command is reveived from input_handler
* @param receive_message_id id of the messages to read
* @param transmit_message_id id of the messages to transmit. 0 if nothing to transmit
*/
void CanIOThread::Run(std::future<void> *future, uint8_t *receive_message_id, size_t receive_message_id_size)
{ //TODO break, list of IDs to listed to. Do not need the promise {
    size_t i = 0;
    std::future_status future_status;
    do
    {
        //READ FROM SOCKET
        scpp::CanFrame fr;
        auto result = this->socket->read(fr);
        if (result == scpp::STATUS_OK)
        {
            for (size_t i = 0; i < receive_message_id_size; i++) {
                if (receive_message_id[i] == fr.id) {
                    CanBuffer::GetInstance().AddRx(&fr.id, fr.data, &fr.len);
                    break;
                }
            }
        }else if (result != scpp::STATUS_NOTHING_TO_READ) {
            std::cout << "Error reading from socket: " << result <<std::endl;
            break;
        }

        //WRITE TO SOCKET
        if (!CanBuffer::GetInstance().TransmitBufferEmpty())
        {
            CanData transmit_data = CanBuffer::GetInstance().PullTx();
            this->socket->write(transmit_data.payload, transmit_data.id, transmit_data.length);
        }

        future_status = future->wait_for(std::chrono::microseconds(10));
    } while (future_status != std::future_status::ready);
}

/*!
* Destructor of CanIOThread. Informs the thread to stop (the Run function) and wait until it is done.
*/
CanIOThread::~CanIOThread() {
    this->thread.join();
}
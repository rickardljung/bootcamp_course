#include "can_io_thread.h"
#include <iostream>
#include "user_input.h"

/*!
* Constructor of CanIOThread. Assigns the class members and starts a thread on the function "Run"
* @param socket used for read and write data to can
* @param receive_message_id id of the messages to read
* @param transmit_message_id id of the messages to transmit. 0 if nothing to transmit
*/
CanIOThread::CanIOThread(scpp::SocketCan *socket, std::promise<void> *promise, uint8_t receive_message_id, uint8_t transmit_message_id) {
    this->socket = socket;
    this->thread = std::thread(&CanIOThread::Run, this, promise, receive_message_id, transmit_message_id);
}

/*!
* Reads data from CAN and writes it to the receive buffer. Pulls data from the transmit buffer and transmits it to can.
* Loops until a "end simulation" command is reveived from input_handler
* @param receive_message_id id of the messages to read
* @param transmit_message_id id of the messages to transmit. 0 if nothing to transmit
*/
void CanIOThread::Run(std::promise<void> *promise, uint8_t receive_message_id, uint8_t transmit_message_id) {
    while (1)
    {
        scpp::CanFrame fr;
        if (this->socket->read(fr) == scpp::STATUS_OK)
        {
            //always stop thread if receiving "end simulation" command from user.
            if (fr.id == 1) {
                UserInput *input = reinterpret_cast<UserInput*>(fr.data);
                if(input->end_simulation)
                {
                    promise->set_value();
                    break;
                }
            }
            if (fr.id == receive_message_id) {
                CanBuffer::GetInstance().AddRx(fr.data);
            }
        }
        //transmit_message_id = 0 -> nothing to send
        if (transmit_message_id != 0)
        {
            this->socket->write(CanBuffer::GetInstance().PullTx(), transmit_message_id, 8);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

/*!
* Destructor of CanIOThread. Informs the thread to stop (the Run function) and wait until it is done.
*/
CanIOThread::~CanIOThread() {
    this->thread.join();
}
#include "can_io_thread.h"
#include <iostream>
#include "user_input.h"

/*!
* Constructor of CanIOThread. Assigns the class members and starts a thread on the function "Run"
* @param socket used for read and write data to can
* @param receive_message_id id of the messages to read
* @param transmit_message_id id of the messages to transmit. 0 if nothing to transmit
*/
CanIOThread::CanIOThread(scpp::SocketCan *socket, std::promise<void> *promise, uint8_t receive_message_id, uint8_t transmit_message_id) { //TODO break lines
    this->socket = socket;
    this->thread = std::thread(&CanIOThread::Run, this, promise, receive_message_id, transmit_message_id);
}

/*!
* Reads data from CAN and writes it to the receive buffer. Pulls data from the transmit buffer and transmits it to can.
* Loops until a "end simulation" command is reveived from input_handler
* @param receive_message_id id of the messages to read
* @param transmit_message_id id of the messages to transmit. 0 if nothing to transmit
*/
void CanIOThread::Run(std::promise<void> *promise, uint8_t receive_message_id, uint8_t transmit_message_id) { //TODO break, list of IDs to listed to. Do not need the promise {
    size_t i = 0;
    while (true)
    {
        scpp::CanFrame fr;
        auto result = this->socket->read(fr);
        if (result == scpp::STATUS_OK)
        {
            i = 0;
            if (fr.id == 1) { //always stop thread if receiving "end simulation" command from user.
                UserInput *input = reinterpret_cast<UserInput*>(fr.data);
                if(input->end_simulation)
                {
                    promise->set_value();
                    break;
                }
            }
            if (fr.id == receive_message_id) {
                CanBuffer::GetInstance().AddRx(fr.data); //TODO: not singleton?
            }
        }
        else if(result == scpp::STATUS_NOTHING_TO_READ)
        {
            if(++i>20000)
            {
                std::cout << "ended here" << std::endl;
                promise->set_value();
                break;
            }
            else{continue;}
        }

        else if (result != scpp::STATUS_OK) {
            std::cout << "Error reading from socket: " << result <<std::endl;
            break;
        }

        //transmit_message_id = 0 -> nothing to send
        if (transmit_message_id != 0)
        {
            //this->socket->write(CanBuffer::GetInstance().PullTx(), transmit_message_id, 8);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}

/*!
* Destructor of CanIOThread. Informs the thread to stop (the Run function) and wait until it is done.
*/
CanIOThread::~CanIOThread() {
    this->thread.join();
}
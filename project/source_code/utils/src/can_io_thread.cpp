#include "can_io_thread.h"
#include <iostream>
#include "user_input.h"

/*!
* Constructor of CanIOThread. Assigns the class members and starts a thread on the function "Run"
* @param socket used for read and write data to can
* @param receive_message_id id of the messages to read
* @param transmit_message_id id of the messages to transmit. 0 if nothing to transmit
*/
CanIOThread::CanIOThread(scpp::SocketCan *socket, uint8_t receive_message_id, uint8_t transmit_message_id) {
    this->socket = socket;
    read_can_thread = std::thread(&CanIOThread::Run, this, receive_message_id, transmit_message_id);
    read_can_thread.detach();
}

/*!
* Reads data from CAN and writes it to the receive buffer. Pulls data from the transmit buffer and transmits it to can.
* Loops until a "end simulation" command is reveived from input_handler
* @param receive_message_id id of the messages to read
* @param transmit_message_id id of the messages to transmit. 0 if nothing to transmit
*/
void CanIOThread::Run(uint8_t receive_message_id, uint8_t transmit_message_id) {
    uint8_t payload[8];
    size_t i=0;
    while (!this->stop_thread)
    {
        scpp::CanFrame fr;
        auto result = this->socket->read(fr);
        if (result == scpp::STATUS_OK)
        {
            //always stop thread if receiving "end simulation" command from user.
            if (fr.id == 1) {
                UserInput *input = reinterpret_cast<UserInput*>(fr.data);
                if(input->end_simulation)
                {
                    this->stop_thread = true;
                }
            }
            if (fr.id == receive_message_id) {
                CanBuffer::GetInstance().AddRx(fr.data);
            }
        }
        
        else if(result == scpp::STATUS_NOTHING_TO_READ)
        {
            if(++i>2000) {break;}
            else{continue;}
        }

        else if (result != scpp::STATUS_OK) {
            std::cout << "Error " << result <<std::endl;
            break;
        }
        else i =0;
        std::this_thread::sleep_for(std::chrono::milliseconds(3));


        //transmit_message_id = 0 -> nothing to send
        if (transmit_message_id != 0)
        {
            this->socket->write(CanBuffer::GetInstance().PullTx(), transmit_message_id, 8);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    if (this->stop_thread) //TODO: promise instead??
    {
        thread_stopped = true;
    }
}

/*!
* Destructor of CanIOThread. Informs the thread to stop (the Run function) and wait until it is done.
*/
CanIOThread::~CanIOThread() {
    this->stop_thread = true;
    while (!thread_stopped) {
        for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
    }
}
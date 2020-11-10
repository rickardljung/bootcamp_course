#include "can_reader.h"
#include <iostream>

CanReader::CanReader(scpp::SocketCan *socket, uint8_t message_id) {
    this->socket = socket;
    this->read_can_thread = std::thread(&CanReader::Run, this, message_id);
    this->read_can_thread.detach();
}

void CanReader::Run(uint8_t message_id) {

    const uint8_t msg_id = 2;
    const uint8_t msg_len = 1;
    //payload to be sent in canframe
    uint8_t payload[msg_len];

    while (!this->stop_thread)
    {
        scpp::CanFrame fr;
        auto result = this->socket->read(fr);
        if ((result == scpp::STATUS_OK) || (result == scpp::STATUS_NOTHING_TO_READ))
        {
            if(fr.id == 1)
            {
                
            }
            else if (fr.id == message_id) {
                std::cout << "Received Acc: " << static_cast<int>(fr.data[0]) << std::endl;

                payload[0] = fr.data[0] * 3;
                socket->write(payload, 2, 1);

                CanBuffer::GetInstance().Add(fr.data);
            }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
    if (this->stop_thread) //TODO: promise instead??
    {
        thread_stopped = true;
    }
}

CanReader::~CanReader() {
    this->stop_thread = true;
    while (!thread_stopped) {
        for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
    }
}
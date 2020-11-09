#include "can_reader.h"
#include <iostream>

CanReader::CanReader(scpp::SocketCan *socket, uint8_t message_id) {
    this->socket = socket;
    read_can_thread = std::thread(&CanReader::Run, this, message_id);
    read_can_thread.detach();
}

void CanReader::Run(uint8_t message_id) {
    while (!this->stop_thread)
    {
        scpp::CanFrame fr;
        if (this->socket->read(fr) == scpp::STATUS_OK)
        {
            if (fr.id == message_id) {
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
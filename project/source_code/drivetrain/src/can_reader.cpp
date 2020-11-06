#include "can_reader.h"
#include <iostream>

CanReader::CanReader(scpp::SocketCan *socket) {
    this->socket = socket;
    read_can_thread = std::thread(&CanReader::Run, this);
    read_can_thread.detach();
}

#include <unordered_map>

void CanReader::Run(uint8_t message_id) {
    while (!this->stop_thread)
    {
        //TODO: if statement checking if a "end simulation" is received
        scpp::CanFrame fr;
        if (this->socket->read(fr) == scpp::STATUS_OK)
        {
            if (fr.id == 1) {
                /*
                user_input.accelerator_pedal = fr.data[0];
                //std::cout << "pedal: " << static_cast<int>(fr.data[0]) << std::endl;
                user_input.break_pedal       = fr.data[1];
                user_input.gear_position     = fr.data[2];
                user_input.ignition          = fr.data[3];
                */
                CanBuffer::GetInstance().Add(fr.data);
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        } else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
    if (this->stop_thread)
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
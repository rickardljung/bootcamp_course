#include "drivetrain_input_reader.hpp"
#include <iostream>

DriveTrainReader::DriveTrainReader() {
    read_can_thread = std::thread(&DriveTrainReader::run, this);
    read_can_thread.detach();
}

bool DriveTrainReader::Initialize(std::string can_network_name) {
    this->socket_initialized  = socket_can.Initialize(can_network_name);

    return this->socket_initialized;
}

void DriveTrainReader::run() {
    while (!this->stop_thread) {
        if (this->socket_initialized) {
            scpp::CanFrame fr;

            //TODO: if statement checking if a "end simulation" is received

            if (socket_can.read(fr) == scpp::STATUS_OK) {
                user_input_struct user_input, user_input_2;
                user_input.acc = fr.data[0];
                user_input.brk = fr.data[1];
                user_input.gear = fr.data[2];
                user_input.ignition = fr.data[3];

                CanBuffer::getInstance().add(&user_input);
            } else {
                for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
            }
        }
        if (this->stop_thread) {
            thread_stopped = true;
        }
    }
}

DriveTrainReader::~DriveTrainReader() {
    this->stop_thread = true;
    while (!thread_stopped) {
        for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
    }
}
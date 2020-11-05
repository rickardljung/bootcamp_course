#ifndef DRIVETRAIN_INPUT_READER_H
#define DRIVETRAIN_INPUT_READER_H

#include "user_input.hpp"
#include "can_buffer.hpp"
#include <thread>
#include "socketcan.h"
#include <string>

class DriveTrainReader {
    private:
        std::thread read_can_thread;
        scpp::SocketCan socket_can;
        void run();
        bool stop_thread = false;
        bool thread_stopped = false;
        bool socket_initialized = false;
    public:
        DriveTrainReader();
        ~DriveTrainReader();
        bool Initialize(std::string can_network_name);
};

#endif
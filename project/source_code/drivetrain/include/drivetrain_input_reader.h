#ifndef DRIVETRAIN_INPUT_READER_H
#define DRIVETRAIN_INPUT_READER_H

#include "user_input.h"
#include "can_buffer.h"
#include <thread>
#include "socketcan.h"
#include <string>

class DriveTrainReader {
    private:
        std::thread read_can_thread;
        scpp::SocketCan socket_can;
        void Run();
        bool stop_thread = false;
        bool thread_stopped = false;
        bool socket_initialized = false;
    public:
        DriveTrainReader();
        ~DriveTrainReader();
        bool Initialize(std::string can_network_name);
};

#endif
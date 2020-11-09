#ifndef can_reader_H
#define can_reader_H

#include "user_input.h"
#include "can_buffer.h"
#include <thread>
#include "socketcan.h"
#include <string>

class CanReader {
    private:
        std::thread read_can_thread;
        scpp::SocketCan *socket;
        void Run(uint8_t message_id);
        bool stop_thread = false;
        bool thread_stopped = false;
        bool socket_initialized = false;
    public:
        CanReader(scpp::SocketCan *socket, uint8_t message_id);
        ~CanReader();
        scpp::SocketCan * get_socket();
};

#endif
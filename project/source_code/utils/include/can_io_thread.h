#ifndef can_reader_H
#define can_reader_H

#include "user_input.h"
#include "can_buffer.h"
#include <thread>
#include "socketcan.h"
#include <string>
#include <future>

class CanIOThread {
    private:
        std::thread thread;
        scpp::SocketCan *socket;
        void Run(std::promise<void> *promise, uint8_t message_id, uint8_t transmit_message_id);
        bool stop_thread = false;
        bool thread_stopped = false;
        bool socket_initialized = false;
    public:
        CanIOThread(scpp::SocketCan *socket, std::promise<void> *promise, uint8_t receive_message_id, uint8_t transmit_message_id);
        ~CanIOThread();
        scpp::SocketCan * get_socket();
};

#endif
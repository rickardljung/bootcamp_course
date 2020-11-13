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
        void Run( std::future<void> *future, uint8_t message_id, uint8_t transmit_message_id);
    public:
        CanIOThread(scpp::SocketCan *socket,  std::future<void> *future, uint8_t receive_message_id, uint8_t transmit_message_id);
        ~CanIOThread();
        scpp::SocketCan * get_socket();
};

#endif
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
        void Run( std::future<void> *future, uint8_t *receive_message_id, size_t receive_message_id_size);
    public:
        CanIOThread(scpp::SocketCan *socket,  std::future<void> *future, uint8_t *receive_message_id, size_t receive_message_id_size);
        ~CanIOThread();
        scpp::SocketCan * get_socket();
};

#endif
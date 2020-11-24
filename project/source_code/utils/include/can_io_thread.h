#ifndef can_reader_H
#define can_reader_H

#include "socketcan.h"
#include "user_input.h"
#include "can_buffer.h"

#include <string>
#include <thread>
#include <future>

template <typename P>
class CanIOThread {
    private:
        std::thread thread;
        scpp::SocketCan *socket;
        void Run(std::future<void> *future, uint8_t *receive_message_id, const size_t &receive_message_id_size);
    public:
        CanIOThread(scpp::SocketCan *socket,  std::future<void> *future, uint8_t *receive_message_id,
                    const size_t &receive_message_id_size, P& canbuffer);
        ~CanIOThread();
        scpp::SocketCan * get_socket();
        P& canbuffer;
};

#endif
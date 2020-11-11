#ifndef can_reader_H
#define can_reader_H

#include "user_input.h"
#include "can_buffer.h"
#include <thread>
#include "socketcan.h"
#include <string>

class CanIOThread {
    private:
        std::thread read_can_thread;
        scpp::SocketCan *socket;
        void Run(uint8_t message_id, uint8_t transmit_message_id);
        bool stop_thread = false;
        bool thread_stopped = false;
        bool socket_initialized = false;
    public:
<<<<<<< HEAD:project/source_code/utils/include/can_reader.h
        CanReader(scpp::SocketCan *socket, uint8_t message_id);

        ~CanReader();
=======
        CanIOThread(scpp::SocketCan *socket, uint8_t receive_message_id, uint8_t transmit_message_id);
        ~CanIOThread();
>>>>>>> e737c99ba1fe05ef31dbeb1a04011f87847dc37a:project/source_code/utils/include/can_io_thread.h
        scpp::SocketCan * get_socket();
};

#endif
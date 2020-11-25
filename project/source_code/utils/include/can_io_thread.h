#ifndef can_reader_H
#define can_reader_H

#include "socketcan.h"
#include "user_input.h"
#include "can_buffer.h"
#include "can_io_thread.h"

#include <string>
#include <thread>
#include <future>
#include <iostream>

template <typename P>
class CanIOThread {
    private:
        std::thread thread;
        scpp::SocketCan *socket;
        void Run(std::future<void> *future, uint8_t *receive_message_id, const size_t &receive_message_id_size);
        std::unordered_map<int, CanData> candata_tx;
    public:
        CanIOThread(scpp::SocketCan *socket,  std::future<void> *future, uint8_t *receive_message_id,
                    const size_t &receive_message_id_size, P& canbuffer);
        ~CanIOThread();
        scpp::SocketCan * get_socket();
        P& canbuffer_tx;
        P& canbuffer_rx;
};


/*!
* Constructor of CanIOThread. Assigns the class members and starts a thread on the function "Run"
* @param socket used for read and write data to can
* @param receive_message_id list of IDs that should be read
* @param receive_message_id_size size of the list receive_message_id.
*/
template <typename P>
CanIOThread<P>::CanIOThread(scpp::SocketCan *_socket, std::future<void> *future, uint8_t *receive_message_id,
                         const size_t &receive_message_id_size, P& canbuffer_tx, P& canbuffer_tx)
                         : socket(_socket),
                           canbuffer_tx(_canbuffer),
                           canbuffer_rx(_canbuffer),
                         thread(std::thread(&CanIOThread::Run, this, future, receive_message_id, receive_message_id_size)) {}

/*!
* Reads data from CAN and writes it to the receive buffer. Pulls data from the transmit buffer and transmits it to can.
* Loops until a the future is set from outside of this class.
* @param future future which will notify when the execution (the loop) should end
* @param receive_message_id list of IDs that should be read
* @param receive_message_id_size size of the list receive_message_id.
*/
template <typename P>
void CanIOThread<P>::Run(std::future<void> *future, uint8_t *receive_message_id, const size_t &receive_message_id_size)
{
    size_t i = 0;
    std::future_status future_status;
    do
    {
        //READ FROM SOCKET
        scpp::CanFrame fr;
        auto result = this->socket->read(fr);
        if (result == scpp::STATUS_OK)
        {
            for (size_t i = 0; i < receive_message_id_size; i++) {
                if (receive_message_id[i] == fr.id) {
                    canbuffer_rx.Add(fr.id, fr.data, fr.len);
                    break;
                }
            }
        }else if (result != scpp::STATUS_NOTHING_TO_READ) {
            std::cout << "Error reading from socket: " << result <<std::endl;
            break;
        }

        //WRITE TO SOCKET
        //if (!CanBuffer::GetInstance().TransmitBufferEmpty())
        //TODO: might not work with ringbuffer
        candata_tx = canbuffer_tx.Pull();
        if(transmit_data.id != 0) //do not transmit until data is added to the tranmit buffer. 0 as init
        {
            for(int i = 0, i<candata_tx.size(), i++)
            {
                this->socket->write(candata_tx[i].payload, candata_tx[i].id, candata_tx[i].length);
            }
        }

        future_status = future->wait_for(std::chrono::microseconds(10));
    } while (future_status != std::future_status::ready);
}

/*!
* Destructor of CanIOThread. Informs the thread to stop (the Run function) and wait until it is done.
*/
template <typename P>
CanIOThread<P>::~CanIOThread()
{
    this->thread.join();
}

#endif
#ifndef CANSOCKET_H
#define CANSOCKET_H
#include <cstdint>

#include <linux/can.h>

namespace scpp{

struct CanFrame {
    uint32_t id = 0;
    uint8_t len = 0;
    uint8_t flags = 0;
    uint8_t data[64];

};

enum SocketCanStatus {
    STATUS_OK = 1 << 0,
    STATUS_SOCKET_CREATE_ERROR = 1 << 2,
    STATUS_INTERFACE_NAME_TO_IDX_ERROR = 1 << 3,
    STATUS_MTU_ERROR = 1 << 4, /// maximum transfer unit
    STATUS_CANFD_NOT_SUPPORTED = 1 << 5, /// Flexible data-rate is not supported on this interface
    STATUS_ENABLE_FD_SUPPORT_ERROR = 1 << 6, /// Error on enabling fexible-data-rate support
    STATUS_WRITE_ERROR = 1 << 7,
    STATUS_READ_ERROR = 1 << 8,
    STATUS_BIND_ERROR = 1<<9,
    STATUS_NOTHING_TO_READ ,
};


class SocketCan {
public:
    SocketCan() = default;
    SocketCan(const SocketCan &) = delete;
    SocketCan & operator=(const SocketCan &) = delete;
    SocketCanStatus open(const char * can_interface);
    SocketCanStatus write(const uint8_t *_data, const uint32_t &_id,const uint8_t &_len);
    SocketCanStatus write(const CanFrame & msg);
    SocketCanStatus write(struct canfd_frame *frame);
    SocketCanStatus read(CanFrame & msg);
    ~SocketCan();
private:
    int m_socket = -1;
    int32_t m_read_timeout_ms = 3;

};
}

#endif // CANSOCKET_H

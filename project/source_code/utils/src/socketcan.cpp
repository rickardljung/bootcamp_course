#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <unistd.h>
#include <cstring>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can/raw.h>
#include "socketcan.h"
#include <fcntl.h>

namespace scpp{

/** Returns true on success, or false if there was an error */
bool SetSocketBlockingEnabled(int fd, bool blocking)
{
   if (fd < 0) return false;

   int flags = fcntl(fd, F_GETFL, 0);

   flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);

   return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
}

SocketCanStatus SocketCan::open(const char *can_interface) {
    /* open socket */
    if ((m_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        std::cerr << "socket" << std::endl;
        return STATUS_SOCKET_CREATE_ERROR;
    }
    struct sockaddr_can addr;
    struct ifreq ifr;

    strncpy(ifr.ifr_name, can_interface, IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = '\0';
    ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
    if (!ifr.ifr_ifindex) {
        std::cerr << "if_nametoindex" << std::endl;
        return STATUS_INTERFACE_NAME_TO_IDX_ERROR;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    //struct timeval tv;
    //tv.tv_sec = 0;  /* 30 Secs Timeout */
    //tv.tv_usec = m_read_timeout_ms * 1000;  // Not init'ing this can cause strange errors
    int optval = 7;

    if (!SetSocketBlockingEnabled(m_socket,false)) {
        std::cerr << "nonn block" << std::endl;
        return STATUS_BIND_ERROR;
    }
    setsockopt(m_socket, SOL_SOCKET, /*SO_RCVTIMEO*/SO_PRIORITY, /*(const char*)*/&optval,sizeof(optval));

    if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cerr << "bind" << std::endl;
        return STATUS_BIND_ERROR;
    }
    return STATUS_OK;
}

SocketCanStatus SocketCan::write(const uint8_t *_data, const uint32_t &_id, const uint8_t &_len) {
    struct canfd_frame frame;
    memset(&frame, 0, sizeof(frame));
    frame.can_id = _id;
    frame.len = _len;
    memcpy(frame.data, _data, frame.len);
    return this->write(&frame);
}

SocketCanStatus SocketCan::write(const CanFrame & msg) {
    struct canfd_frame frame;
    memset(&frame, 0, sizeof(frame)); /* init CAN FD frame, e.g. LEN = 0 */
    //convert CanFrame to canfd_frame
    frame.can_id = msg.id;
    frame.len = msg.len;
    frame.flags = msg.flags;
    memcpy(frame.data, msg.data, msg.len);
    return this->write(&frame);
}

SocketCanStatus SocketCan::write(struct canfd_frame *frame) {
    /* send frame */
    if (::write(m_socket, frame, int(CAN_MTU)) != int(CAN_MTU)) {
        std::cerr << "write" << std::endl;
        return STATUS_WRITE_ERROR;
    }
    return STATUS_OK;
}

SocketCanStatus SocketCan::read(CanFrame & msg) {
    struct canfd_frame frame;
    // Read in a CAN frame
    auto num_bytes = ::read(m_socket, &frame, CAN_MTU /*CANFD_MTU*/);
    if (num_bytes == 0 ||
            (num_bytes != CAN_MTU && errno == 11)) return STATUS_NOTHING_TO_READ;
    else if (num_bytes != CAN_MTU) {
        std::cout <<errno<<" READ ERRORNO : " <<strerror(errno) << std::endl;
        return STATUS_READ_ERROR;
    }

    msg.id = frame.can_id;
    msg.len = frame.len;
    msg.flags = frame.flags;
    memcpy(msg.data, frame.data, frame.len);
    return STATUS_OK;
}

SocketCan::~SocketCan() {
    ::close(m_socket);
}
}
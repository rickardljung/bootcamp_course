//create a singleton class with RingBuffer
//https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
#ifndef CAN_BUFFER_H
#define CAN_BUFFER_H
#include "can_buffer.h"
#include "user_input.h"

#include <unordered_map>

const int NBR_TX_FRAMES = 2;

typedef struct CanData_struct{
    uint32_t id = 0;
    uint8_t payload[8] = {0,0,0,0,0,0,0,0};
    uint8_t length = 0;
} CanData;

class CanBuffer
{
    public:
        CanBuffer()=default;
        void Add(const uint32_t& id, uint8_t payload[],const uint8_t& length);
        std::unordered_map<int, CanData> CanBuffer::Pull();
    private:    
        std::unordered_map<int, CanData> candata;
        std::mutex buffer_mutex;
};

#endif
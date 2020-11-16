#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <cstdint>
#include <mutex>

const uint32_t msg_id = 1;
const uint8_t msg_len = 3;
const unsigned int P = 0;
const unsigned int N = 1;
const unsigned int D = 2;
const unsigned int R = 3;
const unsigned int ignition_on = 1;
const unsigned int ignition_off = 0;
const unsigned int end = 1;

typedef struct user_input_struct {
    uint8_t accelerator_pedal;
    uint8_t brake_pedal;
    uint8_t gear_position   : 2;
    uint8_t ignition        : 1;
    uint8_t end_simulation  : 1;
    uint8_t reserved        : 4;
} UserInput;

void EncodePayload(uint8_t *payload, std::mutex* mtx, UserInput *user_input);

#endif
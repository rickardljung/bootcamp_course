#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <cstdint>
#include <mutex>

const uint32_t msg_id = 1;
const uint8_t msg_len = 3;

const uint32_t misc_msg_id = 3;
const uint8_t misc_msg_len = 1;

const uint8_t P = 0;
const uint8_t N = 1;
const uint8_t D = 2;
const uint8_t R = 3;
const uint8_t ignition_on = 1;
const uint8_t ignition_off = 0;
const uint8_t end = 1;

typedef struct user_input_struct {
    uint8_t accelerator_pedal;
    uint8_t brake_pedal;
    uint8_t gear_position   : 2;
    uint8_t ignition        : 1;
    uint8_t end_simulation  : 1;
    uint8_t reserved        : 4;
} UserInput;

typedef struct misc_input_struct {
    uint8_t hazard_light     : 1; // a
    uint8_t right_blinker    : 1; // .
    uint8_t left_blinker     : 1; // ,
    uint8_t hand_brake       : 1; // h should be in user_input_struct
    uint8_t _reserved_pad    : 4;
} MiscInput;

void EncodePayload(uint8_t *payload, std::mutex* mtx, UserInput *user_input);

#endif
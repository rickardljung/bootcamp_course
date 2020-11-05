#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <cstdint>

typedef struct user_input_st {
    uint8_t acc;
    uint8_t brk;
    uint8_t gear;
    uint8_t ignition;
} user_input_struct;

#endif
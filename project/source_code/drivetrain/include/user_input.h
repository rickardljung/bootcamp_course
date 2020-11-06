#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <cstdint>

typedef struct user_input_struct {
    uint8_t accelerator_pedal;
    uint8_t break_pedal;
    uint8_t gear_position;
    uint8_t ignition;
} UserInput;

#endif
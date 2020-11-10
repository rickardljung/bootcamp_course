#ifndef CAN_FR_HANDLER_H
#define CAN_FR_HANDLER_H
#include <iostream>

enum GearPos : uint8_t {P=0, N=1, D=2, R=3};
const uint8_t msg_id = 1;
const uint8_t msg_len = 5;

typedef struct user_input_struct {
    uint8_t accelerator_pedal=0;
    uint8_t brake_pedal=0;
    GearPos gear_position=P;
    uint8_t ignition=0;
    uint8_t end_simulation=0;
} UserInput;

void EncodePayload(uint8_t *_payload, UserInput *user_input);


#endif
#include "user_input.h"

void EncodePayload(uint8_t *_payload, UserInput *user_input)
{
    _payload[0] = user_input->accelerator_pedal;
    _payload[1] = user_input->brake_pedal;
    _payload[2] = user_input->gear_position;
    _payload[3] = user_input->ignition;
    _payload[4] = user_input->end_simulation;
}
#include "user_input.h"
/*!
	* Fills the payload array that is to be sent on CAN with information from the UserInput struct.
	* @param _payload array to be sent in a CAN frame.
    * @param user_input struct to receive values from.
	* @return Nothing is returned
*/
void EncodePayload(uint8_t *_payload, UserInput *user_input, std::mutex *mtx)
{
    mtx->lock();
    _payload[0] = user_input->accelerator_pedal;
    _payload[1] = user_input->brake_pedal;
    _payload[2] = user_input->gear_position;
    _payload[3] = user_input->ignition;
    _payload[4] = user_input->end_simulation;
    mtx->unlock();
}
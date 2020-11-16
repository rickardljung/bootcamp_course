#include <cstring>
#include "user_input.h"

/*!
	* Fills the payload array that is to be sent on CAN with information from the UserInput struct.
	* @param payload array to be sent in a CAN frame.
    * @param user_input struct to receive values from.
	* @return Nothing is returned
*/
void EncodePayload(uint8_t *payload, std::mutex* mtx, UserInput *user_input)
{
    std::lock_guard<std::mutex> lock (*mtx);
    std::memcpy(payload, user_input,sizeof(UserInput));
}
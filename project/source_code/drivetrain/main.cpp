//#include "vehicle.hpp"
#include "user_input.hpp"
#include "can_reader.hpp"
#include "ringbuffer.hpp"
#include <iostream>

int main() {


    Ringbuffer<user_input, 50> buffer;
    CanReader reader(&buffer); //thread which will write to buffer

    /*
    Vehicle v(&buffer);

    v.run();

    delete input;

    */
}
#include "ringbuffer.hpp"

template <typename T, size_t size>
void Ringbuffer<T, size>::add(T item) {
    this->buffer[add_index] = item;
    add_index++;
    if (add_index >= size) {
        add_index = 0;
    }
    //ringbuffer full, oldest item is overwritten
    if (add_index == get_index) {
        get_index++;
    }
}

template <typename T, size_t size>
T* Ringbuffer<T, size>::get() {
    T next_item = nullptr;
    if(add_index != get_index) {
        next_item = buffer[get_index];
        get_index++;
    }
    return next_item;
}


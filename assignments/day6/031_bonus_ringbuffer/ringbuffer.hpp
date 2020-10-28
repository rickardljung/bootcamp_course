#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <iostream>

template <typename T, size_t size = 100>
class Ringbuffer {
    private:
        T      *buffer = new T[size];
        size_t get_index = 0;
        size_t add_index = 0;
    public:
        Ringbuffer() = default;
        ~Ringbuffer() {delete [] buffer;};
        T get();
        void add(T item);
        bool isEmpty();
};

//since its a template should also the implementation be in the hpp file
template <typename T, size_t size>
void Ringbuffer<T, size>::add(T item) {
    this->buffer[add_index%size] = item;

    //ringbuffer full, oldest item is overwritten
    if (get_index%size > add_index%size) {
        get_index = add_index;
    }

    add_index++;
}

template <typename T, size_t size>
T Ringbuffer<T, size>::get() {
    T next_item = buffer[get_index%size];
    if (get_index < add_index) {
        get_index++;
    }
    return next_item;
}

#endif
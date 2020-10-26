#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <iostream>

template <typename T, size_t size = 100>
class Ringbuffer {
    private:
        T *buffer = new T[size];
        size_t get_index = 0;
        size_t add_index = 0;
    public:
        //Ringbuffer() = default();
        ~Ringbuffer();
        void add(T item);
        T * get();
};


#endif
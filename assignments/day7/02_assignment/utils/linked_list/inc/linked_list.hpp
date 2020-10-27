#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

typedef struct struct_list_element{
    //int number;
    void *object;
    struct struct_list_element *next = nullptr;
} list_element;

class LinkedList {
    private:
    list_element * findElement(unsigned int index);
    list_element *first_element = nullptr;

    public:
        LinkedList() = default;
        void add(void *object, unsigned int index);
        void remove(unsigned int index);
        void printList();
        void * getObject(unsigned int index);
};

#endif
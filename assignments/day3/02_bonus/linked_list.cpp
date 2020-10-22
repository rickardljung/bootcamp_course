#include <iostream>
#include "linked_list.hpp"

list_element * LinkedList::findElement(unsigned int index){
    list_element *current_element = this->first_element;
    for(int i = 0; i < index; i++) {
        current_element = current_element->next;
    }
    return current_element;
}

void LinkedList::add(void *object, unsigned int index) {
    list_element *current_element = this->first_element;
    if (this->first_element == nullptr) {
        this->first_element = new list_element;
        current_element = this->first_element;
    } else {
        if (index == 0) { //add first in list
            current_element = new list_element;
            current_element->next = first_element;
            first_element = current_element;
        } else {
            current_element = findElement(index-1); //find the element to add the new element after
            list_element *next_element = current_element->next;
            current_element->next = new list_element;
            current_element = current_element->next;
            current_element->next = next_element;
        }
    }
    current_element->object = object;
}

void LinkedList::remove(unsigned int index) {
//TODO
}

void * LinkedList::getObject(unsigned int index) {
    return findElement(index)->object;
}
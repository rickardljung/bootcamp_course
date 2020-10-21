#include <iostream>
#include "linked_list.hpp"

list_element * LinkedList::findElement(unsigned int index){
    list_element *current_element = this->first_element;
    for(int i = 0; i < index-1; i++) {
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

}

void * LinkedList::getObject(unsigned int index) {
    return findElement(index)->object;
}

/*
int main()
{
    bool exit = false;
    list_element* first_element = nullptr;
    while(!exit) {
        std::cout << "\nChoose an alternative from the menu below: (1-4) \n1. Add new item to the end of the list\n2. Remove item from the front of the list\n3. Print the list\n4. Exit" << std::endl;
        int user_input;
        std::cin >> user_input;
        if(user_input == 1) { //New item
            int user_number;
            std::cout << std::endl << "Specify a number to add to the list: " << std::endl;
            std::cin >> user_number;
            list_element *current_element = first_element;
            if (first_element == nullptr) {
                first_element = new list_element;
                current_element = first_element;
            } else {
                int user_index;
                std::cout << std::endl << "Specify the index to add the new number to (zero indexed): " << std::endl;
                std::cin >> user_index;
                if (user_index == 0) { //add first in list
                    current_element = new list_element;
                    current_element->next = first_element;
                    first_element = current_element;
                } else {
                    for(int i = 0; i < user_index-1; i++) { //search element to add the new element after
                        current_element = current_element->next;
                    }
                    list_element *next_element = current_element->next;
                    current_element->next = new list_element;
                    current_element = current_element->next;
                    current_element->next = next_element;
                }
            }
            current_element->number = user_number;

        } else if(user_input == 2) { //Remove item
            list_element *remove_element = first_element;
            first_element = first_element->next;
            delete remove_element;
        } else if(user_input == 3) { //Print
            print(first_element);
        } else if(user_input == 4) { //Exit
            exit = true;
        } else {
            std::cout << std::endl << "Invalid input, please try again!" << std::endl;
        }
    }
}
*/
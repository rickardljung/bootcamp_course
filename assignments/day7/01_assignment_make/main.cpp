#include "shapes.hpp"
#include <iostream>

//Write a make file which generates a shared object from the Shape Assignment. Then write another application
//which uses the share object and creates shapes.

int main() {
    Circle c();
    Triangle t();

    std::cout << "Shapes are created!!" << std::endl;

    return 0;
}
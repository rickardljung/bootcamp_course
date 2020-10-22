#include "shapes.hpp"
#include <iostream>

int main() {
    Square c1(2, 2);
    Rectangle c2(1, 4);

    if (c1 == c2) {
        std::cout << "The shapes are EQUAL!" << std::endl;
    } else {
        std::cout << "The shapes are not equal :(" << std::endl;
    }

    if (c1 > c2) {
        std::cout << "c1 is greater than c2" << std::endl;
    } else {
        std::cout << "c1 is less than c2" << std::endl;
    }

    return 0;
}
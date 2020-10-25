#include <iostream>
#include "shapes.hpp"

template <typename T1, typename T2>
void compare(T1 a, T2 b) {
    if (a == b) {
        std::cout << "The shapes are EQUAL!" << std::endl;
    } else {
        std::cout << "The shapes are not equal :(" << std::endl;
    }

    if (a > b) {
        std::cout << "c1 is greater than c2" << std::endl;
    } else {
        std::cout << "c1 is less than c2" << std::endl;
    }
}

int main() {
    Circle c(2,3);
    Rectangle r(4,5);

    compare<Circle&, Rectangle&>(c, r);

    compare<int, int>(14, 13);
}
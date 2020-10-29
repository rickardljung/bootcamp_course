#include "shapes.hpp"
#include <iostream>

template <typename T>
class MockShape : public T{
public:
    MockShape(int x, int y) : T(x, y) {}
    int mock_area() {
        return this->area();
    }
};

bool test0() {
    Circle c1(1, 3);
    Circle c2(1, 3);
    return (c1 == c2);
}

bool test1() {
    Circle c1(1, 3);
    Circle c2(2, 3);
    return !(c1 == c2);
}

bool test2() {
    int radius = 2;
    int pi = 3;
    MockShape<Circle> m(radius,pi);
    return (radius*radius*pi == m.mock_area());
}

bool test3() {
    MockShape<Circle> mc(2,3);
    MockShape<Rectangle> mr(3,4);
    return (mc.mock_area() == mr.mock_area());
}

int main() {
    if (test0()) {
        std::cout << "test0 OK" << std::endl;
    } else {
        std::cout << "test0 NOK" << std::endl;
    }
    if (test1()) {
        std::cout << "test1 OK" << std::endl;
    } else {
        std::cout << "test1 NOK" << std::endl;
    }
    if (test2()) {
        std::cout << "test2 OK" << std::endl;
    } else {
        std::cout << "test2 NOK" << std::endl;
    }
    if (test3()) {
        std::cout << "test3 OK" << std::endl;
    } else {
        std::cout << "test3 NOK" << std::endl;
    }
    return 0;
}
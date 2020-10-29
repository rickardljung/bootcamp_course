#include "shape_interface.hpp"

#ifndef SHAPES_H
#define SHAPES_H

template<typename T>
class MockShape;

class Circle : public Shape{
    public:
        Circle(int x, int y) : Shape(x, y) {} //will call the constructor of shape
    private:
        int area();
        int perimeter();
        friend class MockShape<Circle>;
};

class Triangle : public Shape{
    public:
        Triangle(int x, int y) : Shape(x, y) {}
    private:
        int area();
        int perimeter();
        friend class MockShape<Triangle>;
};

class Rectangle : public Shape{
    public:
        Rectangle(int x, int y) : Shape(x, y) {}
    private:
        int area();
        int perimeter();
        friend class MockShape<Rectangle>;
};

class Square : public Shape{
    public:
        Square(int x, int y) : Shape(x, y) {}
    private:
        int area();
        int perimeter();
        friend class MockShape<Square>;
};

#endif
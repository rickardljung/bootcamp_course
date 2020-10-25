#include "shape_interface.hpp"

#ifndef SHAPES_H
#define SHAPES_H

class Circle : public Shape{
    public:
        Circle(int x, int y) : Shape(x, y) {} //will call the constructor of shape
    private:
        int area();
        int perimeter();
};

class Triangle : public Shape{
    public:
        Triangle(int x, int y) : Shape(x, y) {}
    private:
        int area();
        int perimeter();
};

class Rectangle : public Shape{
    public:
        Rectangle(int x, int y) : Shape(x, y) {}
    private:
        int area();
        int perimeter();
};

class Square : public Shape{
    public:
        Square(int x, int y) : Shape(x, y) {}
    private:
        int area();
        int perimeter();
};

#endif
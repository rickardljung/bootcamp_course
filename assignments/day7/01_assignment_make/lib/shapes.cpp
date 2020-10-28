#include "shapes.hpp"

int Circle::area() {
    int radius = this->x;
    int pi = this->y;
    return radius*radius*pi;
}

int Circle::perimeter() {
    return this->x * 2 * this->y;
}

int Triangle::area() {
    return (this->x * this->y)/2;
}

int Triangle::perimeter() {
    return this->x * 3;
}

int Rectangle::area() {
    return this->x * this->y;
}

int Rectangle::perimeter() {
    return this->x*2 + this->y*2;
}

int Square::area() {
    return this->x * this->y;
}

int Square::perimeter() {
    return this->x*2 + this->y*2;
}

bool operator== (Shape &s1, Shape &s2) {
    bool area = s1.area() == s2.area();
    bool perimeter = false;
    if (area) {
        perimeter = s1.perimeter() == s2.perimeter();
    }
    return perimeter;
}

bool operator> (Shape &s1, Shape &s2) {
    bool area = s1.area() > s2.area();
    bool perimeter = false;
    if (area) {
        perimeter = s1.perimeter() > s2.perimeter();
    }
    return perimeter;
}

bool operator< (Shape &s1, Shape &s2) {
    bool area = s1.area() < s2.area();
    bool perimeter = false;
    if (area) {
        perimeter = s1.perimeter() < s2.perimeter();
    }
    return perimeter;
}
#ifndef SHAPEINTERFACE_H
#define SHAPEINTERFACE_H

class Shape {
private:
    //friend class MockShape<Shape>;
    //friend MockCircle;
protected:
    int x, y;
public:
    Shape (int x, int y);
    virtual int area() = 0;
    virtual int perimeter() = 0;
    friend bool operator== (Shape &s1, Shape &s2); //friend keyword makes it possible for the function to access private members of the class
    friend bool operator> (Shape &s1, Shape &s2); // not really needed in this application since the objects are received as arguments
    friend bool operator< (Shape &s1, Shape &s2); // but could be good practice.
};

#endif
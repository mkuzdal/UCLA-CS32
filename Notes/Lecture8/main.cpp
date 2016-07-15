/** @file: main.cpp */

// Abstract Type: No data members and pure virtual member functions:

#include <iostream>

class Shape
{
    
private:
    double m_x;
    double m_y;
    
public:
    Shape(double x, double y) : m_x(x), m_y(y)
    { std::cout << "Shape Created" << std::endl; }
    virtual ~Shape()
    { std::cout << "Shape Deleted" << std::endl; }
    virtual void move(double xnew, double ynew) = 0;
    virtual void draw() = 0;
    
}; // end Shape


class Rectangle : public Shape
{
    
private:
    double m_dx;
    double m_dy;
    
public:
    Rectangle(double x, double y, double dx, double dy) : Shape(x,y), m_dx(dx), m_dy(dy)
    { std::cout << "Rectangle Created" << std::endl; }
    virtual ~Rectangle()
    { std::cout << "Rectangle Deleted" << std::endl; }
    virtual void move(double xnew, double ynew) {}
    virtual void draw() {}
    
}; // end Rectangle


class Circle : public Shape
{
    
private:
    double m_r;
    
public:
    Circle(double x, double y, double r) : Shape(x,y), m_r(r)
    { std::cout << "Circle Created" << std::endl; }
    virtual ~Circle()
    { std::cout << "Circle Deleted" << std::endl; }
    virtual void move (double xnew, double ynew) {}
    virtual void draw() {}
    
}; // end Circle


class Square : public Rectangle
{
    
public:
    Square(double x, double y, double dx, double dy) : Rectangle(x,y,dx,dy)
    { std::cout << "Square Created" << std::endl; }
    virtual ~Square()
    { std::cout << "Square Deleted" << std::endl; }
    virtual void move(double xnew, double ynew) {}
    virtual void draw() {}
    
};

// ORDER OF CONSTRUCTION:
// 1.   CONSTRUCT THE BASE CLASS
// 2.   CONSTRUCT THE DATA MEMBERS
// 3.   BODY OF CONSTRUCTOR

// ORDER OF DESTRUCTION:
// 1.   BODY OF DESTRUCTOR
// 2.   DELETE THE DATA MEMBERS
// 3.   DELETE THE BASE CLASS

// ABSTRACT CLASSES HAVE TO IMPLEMENT A DESTRUCTOR

/*************
int main()
{
    Square s1(1,2,3,4);
    Circle c1(1,2,3);
}
**************/

// AT LEAST 1 PURE VIRTUAL FUNCTION (e.g., VIRTUAL ... ... = 0;) MAKES A CLASS ABSTRACT;
// i.e., IT CAN NOT BE CREATED ON ITS OWN.
// a.k.a INTERFACE CLASS.

class Device
{
public:
    virtual ~Device() {}
    virtual void write(char c) = 0;
    virtual void reset() = 0;
}; // end Device





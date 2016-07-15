/** @file: inheritcance&polymorphism.cpp */

/***********************************************************************/

// NOT C++!

/*
 pic = empty collection
 pic.add(new Circle(...));
 pic.add(new Rect(...));
 pic.add(new Circle(...));
 pic.add(new Robot(....));   <-- Legal at compile time in this language
 pic.add(new Chicken(...));  <-- Same here, but will likely get an error
 |
 for (k = 0; k < pic.size(); k++)        |
 pic[k]->draw();         <--     Right here
 
 void f(x)
 {
 x.move(..., ...);
 x.draw();
 }
 
 c = new Circle(...);
 f(c);
 */

/***********************************************************************/

//
//  PROBLEM:
//  DIFFERENT OBJECTS CANNOT BE ADDED TO AN ARRAY OF A GIVEN TYPE
//  SO IF SOMETHING WANTS TO BE DONE TO ONE TYPE, THE SAMPE FUNCTIONALITY
//  HAS TO BE AVAILABLE FOR THE OTHER TYPES
//
//  SOLUTION:
//  CREATE A GENERAL OBJECT FOR ALL THE OBJECTS THAT WANT TO BE
//  USED IN THE ARRAY. (i.e., IF YOU WANT SOMETHING TO BE DONE WITH CIRCLES,
//  TRIANGLES, RECTANGLES, etc. YOU CAN MAKE A SINGLE CLASS, "SHAPE", TO GENERALIZE
//  THESE OBJECTS.)
//
//  SHAPE --> GENERALIZES A CIRCLE (NOT ALL SHAPES ARE CIRLCES)
//  A CIRCLE --> SPECIALIZED SHAPE (BUT ALL CIRCLES ARE SHAPES)
//
//  CIRCLE IS A SUBCLASS OF THE SHAPE CLASS
//  SHAPE IS A SUPERCLASS OF CIRCLE, RECTANGLE, etc.
//
//  IN C++, SHAPE IS A BASECLASS OF CIRCLE, RECTANGLE, etc.
//  CIRCLE IS A DERIVED CLASS OF THE SHAPE CLASS


#include <iostream>
using namespace std;

class Shape
{
private:
    double m_x;
    double m_y;
    
public:
    void move(double xnew, double ynew); // This makes it so all shapes can move and be drawn
    virtual void draw() const;           // Virtual means that draw is now dynamically bound
}; // end Shape

class Circle : public Shape // : public Shape tells the compiler that circle is a subclass of shape
{
private:
    double m_r;
    
public:
    Circle(double x, double y, double r);
    virtual void draw() const;
}; // end Circle

class Rect : public Shape
{
private:
    double m_dx;
    double m_dy;
    
public:
    Rect(double x, double y, double dx, double dy);
    virtual void draw() const;
}; // end Rect

void Shape::move(double xnew, double ynew)
{
    m_x = xnew;
    m_y = ynew;
} // end move

//
//  Shape* pictures[100];
//  pic[0] = new Circle(...);   <-- THIS IS ALLOWED
//                                  Because Rect is a shape
//  pic[1] = new Rect(...);
//  pic[2] = new Circle(...);
//  pic[3] = new Chicken(...);  <-- WON'T COMPILE
//                                  Because Chicken is not a shape
//
//
//  void f(Shape& x)
//  {
//      x.move(..., ...);       <-- WORKS BECAUSE SHAPES MOVE IS THE SAME AS THE DERIVED MOVE
//      x.draw();               <-- WON'T WORK YET (DOESN'T KNOW WHICH DRAW TO USE, SO USES SHAPES)
//                              <-- TO FIX MAKE DRAW A VIRTUAL FUNCTION
//  }
//
//
//
//  Circle c(...);
//  f(c);
//  c.move(..., ...);           <-- CALLS SHAPE'S MOVE FUNCTION
//                              <-- NOT CIRCLE'S BECAUSE CIRCLE DOES NOT HAVE A MOVE FUNCTION
//  c.draw();                   <-- CALLS CIRCLE'S DRAW FUNCTION
//
//
//
//
//  for (int k = 0; k < ...; k++)
//  {
//      pic[k]->draw();         <--
//  }
//
//
//  STATIC BINDING:
//  STATIC SAYS DECIDE THIS AT COMPILE TIME
//  THIS IS DONE BY DEFAULT
//
//  DYNAMIC BINDING:
//  GIVEN A FUNCTION NAME DECIDE WHICH FUNCTION TO CALL,
//  BUT DECIDE IT AT RUN TIME
//












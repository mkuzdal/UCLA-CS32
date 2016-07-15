/** @file: main.cpp */
#include <cmath>

class Shape // in the base class, put in everything that all other derived classes contain
{
public:
    Shape(double x, double y);
    virtual void move(double xnew, double ynew);    // with these two lines, now all shapes can be                      moved or be drawn, no matter what type
    virtual void draw() const = 0; // Equal 0 says to the compiler that there will not be an implementation of draw from shape
    // Virtual makes it so draw is decided at compile time
    
private:
    double m_x;
    double m_y;
};

class Rect : public Shape
{
public:
    Rect(double x, double y, double dx, double dy);
    virtual void draw() const;  // this overrides shapes draw
    virtual double diag() const;
    
private:
    double m_dx;
    double m_dy;
}; // Rectangle is a shape

class Circle : public Shape
{
public:
    Circle(double x, double y, double r);
    virtual void draw() const;  // this overrides shapes draw
    
private:
    double m_r;
}; // Circle is a shape

void Shape::move(double xnew, double ynew)
{
    m_x = xnew;
    m_y = ynew;
}

void Shape::draw() const
{
    // ...
    // draw a cloud centered at (m_x, m_y)
    // ...
}

void Rect::draw() const
{
    // ...
    // draw a rectangle with upper left corner at (m_x, m_y), and length and height m_dx, m_dy
    // ...
}

void Circle::draw() const
{
    // ...
    // draw a circle centered at (m_x, m_y) with radius m_r
    // ...
}

Shape::Shape(double x, double y)
:m_x(x), m_y(y)
{
}

Circle::Circle(double x, double y, double r)
:Shape(x,y), m_r(r)
{
}

Rect::Rect(double x, double y, double dx, double dy)
:Shape(x,y), m_dx(dx), m_dy(dy)
{
}

void f(Shape& x)
{
    x.move(5, 2);
    x.draw();
}

class WarningSymbol : public Shape
{
public:
    virtual void move(double xnew, double ynew); // now we have to go back and make move virtual
    virtual void draw() const;
};

void WarningSymbol::move(double xnew, double ynew)
{
    Shape::move(xnew, ynew); // calling this allows it to move like normal, and then do something else:
    // ... flash 3 times ...
    
}

double Rect::diag() const
{
    return (sqrt(m_dx*m_dx + m_dy*m_dy));
}

int main()
{
    Shape* pic[100];
    pic[0] = new Circle(1, 2, 3);
    pic[1] = new Rect;
    pic[2] = new Circle(4, 5, 6);

    for (int i = 0; i < 3; i++)
        pic[i]->draw();
    
    
    Rect r(1, 2, 3, 4);
    r.move(1, 2); // calls Shape::move.
    r.draw();   // calls Rect::draw.
    
    // Because all shapes move the same, but they are not all drawn the same.
    // So we need to implement a specific draw function for each shape.
    
    
    f(r);
    //  Only draws clouds. Why? Because this is a function that takes in a shape so it calls Shape::draw() for the shape, not the shapes specific draw function.
    //  To fix this, we use the word virtual, and put it in the decleration of the draw function in shape.
    //  The compiler thinks "we're passing in a shape, and we are using draw on that shape, therefore, we will use the  shapes draw function on the shape.
    
    WarningSymbol ws;
    ws.move(2,1);    // calls Warning symbols move function.
    
    f(ws);  // calls Shape::move because move is not declared virtual, so in this case, ws will not flash 3 times.
    
    // NEVER ATTEMPT TO OVERRIDE A NON-VIRTUAL FUNCTION.
    
    // BASE CLASES ALWAYS HAVE A VIRTUAL DESTRUCTOR
    
    // BASE CLASES HAVE MEMBER FUNCTION SET = 0 IF THEY ARE TO BE IMPLEMENTED ONLY BY THE DERIVED CLASSES
    
    // AN INTERFACE CLASS IS A CLASS WITH NO DATA MEMBERS AND ONLY PURE VIRTUAL FUNCTIONS (EXCEPT FOR THE DESTRUCTOR WHICH HAS A DO-NOTHING IMPLEMENTATION)
}

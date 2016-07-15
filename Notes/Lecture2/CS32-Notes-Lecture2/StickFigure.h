#ifndef STICK_FIGURE_INCLUDED
#define STICK_FIGURE_INCLUDED

#include <string>

class Circle;

class StickFigure
{
public:
    StickFigure(double b1, double headDiameter, std::string nm, double hx, double hy);
private:
    // Data Members:
    std::string m_name;
    Circle m_head;
    double m_bodyLength;
};

#endif // STICK_FIGURE_INCLUDED
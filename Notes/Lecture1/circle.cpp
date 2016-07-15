#include "circle.h"
#include "globals.h"

#include <iostream>
using namespace std;

circle::circle(double x, double y, double r)
{
    if (r <= 0)
    {
        exit(1);
    }
    m_centerX = x;
    m_centerY = y;
    m_radius = r;
}

double circle::x() const
{
    return m_centerX;
}

double circle::y() const
{
    return m_centerY;
}

double circle::radius() const
{
    return m_radius;
}

void circle::draw() const
{
    //TODO
}

bool circle::scale(double factor)
{
    if (factor <= 0)
        return false;
    m_radius *= factor;
    return true;
}
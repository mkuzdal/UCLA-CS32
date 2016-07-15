#include "StickFigure.h"

#include <string>
#include <iostream>
using namespace std;

StickFigure::StickFigure(double b1, double headDiameter, string nm, double hx, double hy)
: m_name(nm), m_head(hx, hy, headDiameter/2), m_bodyLength(b1)
{
    
}

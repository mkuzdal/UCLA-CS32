#include "circle.h"
#include "globals.h"

#include <cmath>
using namespace std;

double area(const circle& c)
{
    return c.radius() * c.radius() * M_PI;
}